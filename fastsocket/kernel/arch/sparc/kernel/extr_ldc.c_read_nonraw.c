#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  r_data; int /*<<< orphan*/  ackid; } ;
struct TYPE_5__ {TYPE_1__ r; int /*<<< orphan*/  u_data; } ;
struct ldc_packet {int type; int stype; int env; scalar_t__ seqid; TYPE_2__ u; int /*<<< orphan*/  ctrl; } ;
struct TYPE_6__ {scalar_t__ mode; } ;
struct ldc_channel {unsigned long rx_head; unsigned long rx_tail; scalar_t__ chan_state; TYPE_3__ cfg; scalar_t__ rcv_nxt; struct ldc_packet* rx_base; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ECONNRESET ; 
 int EMSGSIZE ; 
 int LDC_ACK ; 
 scalar_t__ LDC_CHANNEL_DOWN ; 
 scalar_t__ LDC_CHANNEL_RESETTING ; 
 int LDC_CTRL ; 
 int LDC_DATA ; 
 int LDC_INFO ; 
 int LDC_LEN ; 
 scalar_t__ LDC_MODE_UNRELIABLE ; 
 int LDC_NACK ; 
 unsigned long LDC_PACKET_SIZE ; 
 int LDC_START ; 
 int LDC_STOP ; 
 int /*<<< orphan*/  RX ; 
 int data_ack_nack (struct ldc_channel*,struct ldc_packet*) ; 
 int ldc_abort (struct ldc_channel*) ; 
 int /*<<< orphan*/  ldcdbg (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int process_control_frame (struct ldc_channel*,struct ldc_packet*) ; 
 unsigned long rx_advance (struct ldc_channel*,unsigned long) ; 
 int rx_bad_seq (struct ldc_channel*,struct ldc_packet*,struct ldc_packet*) ; 
 int rx_data_wait (struct ldc_channel*,unsigned long) ; 
 int /*<<< orphan*/  rx_seq_ok (struct ldc_channel*,scalar_t__) ; 
 int rx_set_head (struct ldc_channel*,unsigned long) ; 
 int /*<<< orphan*/  send_data_ack (struct ldc_channel*) ; 
 unsigned long sun4v_ldc_rx_get_state (int /*<<< orphan*/ ,unsigned long*,unsigned long*,scalar_t__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int read_nonraw(struct ldc_channel *lp, void *buf, unsigned int size)
{
	struct ldc_packet *first_frag;
	unsigned long hv_err, new;
	int err, copied;

	hv_err = sun4v_ldc_rx_get_state(lp->id,
					&lp->rx_head,
					&lp->rx_tail,
					&lp->chan_state);
	if (hv_err)
		return ldc_abort(lp);

	if (lp->chan_state == LDC_CHANNEL_DOWN ||
	    lp->chan_state == LDC_CHANNEL_RESETTING)
		return -ECONNRESET;

	if (lp->rx_head == lp->rx_tail)
		return 0;

	first_frag = NULL;
	copied = err = 0;
	new = lp->rx_head;
	while (1) {
		struct ldc_packet *p;
		int pkt_len;

		BUG_ON(new == lp->rx_tail);
		p = lp->rx_base + (new / LDC_PACKET_SIZE);

		ldcdbg(RX, "RX read pkt[%02x:%02x:%02x:%02x:%08x:%08x] "
		       "rcv_nxt[%08x]\n",
		       p->type,
		       p->stype,
		       p->ctrl,
		       p->env,
		       p->seqid,
		       p->u.r.ackid,
		       lp->rcv_nxt);

		if (unlikely(!rx_seq_ok(lp, p->seqid))) {
			err = rx_bad_seq(lp, p, first_frag);
			copied = 0;
			break;
		}

		if (p->type & LDC_CTRL) {
			err = process_control_frame(lp, p);
			if (err < 0)
				break;
			err = 0;
		}

		lp->rcv_nxt = p->seqid;

		if (!(p->type & LDC_DATA)) {
			new = rx_advance(lp, new);
			goto no_data;
		}
		if (p->stype & (LDC_ACK | LDC_NACK)) {
			err = data_ack_nack(lp, p);
			if (err)
				break;
		}
		if (!(p->stype & LDC_INFO)) {
			new = rx_advance(lp, new);
			err = rx_set_head(lp, new);
			if (err)
				break;
			goto no_data;
		}

		pkt_len = p->env & LDC_LEN;

		/* Every initial packet starts with the START bit set.
		 *
		 * Singleton packets will have both START+STOP set.
		 *
		 * Fragments will have START set in the first frame, STOP
		 * set in the last frame, and neither bit set in middle
		 * frames of the packet.
		 *
		 * Therefore if we are at the beginning of a packet and
		 * we don't see START, or we are in the middle of a fragmented
		 * packet and do see START, we are unsynchronized and should
		 * flush the RX queue.
		 */
		if ((first_frag == NULL && !(p->env & LDC_START)) ||
		    (first_frag != NULL &&  (p->env & LDC_START))) {
			if (!first_frag)
				new = rx_advance(lp, new);

			err = rx_set_head(lp, new);
			if (err)
				break;

			if (!first_frag)
				goto no_data;
		}
		if (!first_frag)
			first_frag = p;

		if (pkt_len > size - copied) {
			/* User didn't give us a big enough buffer,
			 * what to do?  This is a pretty serious error.
			 *
			 * Since we haven't updated the RX ring head to
			 * consume any of the packets, signal the error
			 * to the user and just leave the RX ring alone.
			 *
			 * This seems the best behavior because this allows
			 * a user of the LDC layer to start with a small
			 * RX buffer for ldc_read() calls and use -EMSGSIZE
			 * as a cue to enlarge it's read buffer.
			 */
			err = -EMSGSIZE;
			break;
		}

		/* Ok, we are gonna eat this one.  */
		new = rx_advance(lp, new);

		memcpy(buf,
		       (lp->cfg.mode == LDC_MODE_UNRELIABLE ?
			p->u.u_data : p->u.r.r_data), pkt_len);
		buf += pkt_len;
		copied += pkt_len;

		if (p->env & LDC_STOP)
			break;

no_data:
		if (new == lp->rx_tail) {
			err = rx_data_wait(lp, new);
			if (err)
				break;
		}
	}

	if (!err)
		err = rx_set_head(lp, new);

	if (err && first_frag)
		lp->rcv_nxt = first_frag->seqid - 1;

	if (!err) {
		err = copied;
		if (err > 0 && lp->cfg.mode != LDC_MODE_UNRELIABLE)
			send_data_ack(lp);
	}

	return err;
}