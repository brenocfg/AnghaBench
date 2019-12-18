#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct rds_iw_recv_work {TYPE_2__* r_frag; struct rds_iw_incoming* r_iwinc; } ;
struct rds_header {scalar_t__ h_ack; scalar_t__ h_sport; scalar_t__ h_dport; scalar_t__ h_len; int h_flags; scalar_t__ h_sequence; scalar_t__ h_credit; } ;
struct TYPE_4__ {struct rds_header i_hdr; } ;
struct rds_iw_incoming {TYPE_1__ ii_inc; int /*<<< orphan*/  ii_frags; } ;
struct rds_iw_connection {struct rds_iw_incoming* i_iwinc; struct rds_iw_recv_work* i_recv_data_rem; struct rds_iw_recv_work* i_recvs; struct rds_header* i_recv_hdrs; } ;
struct rds_iw_ack_state {int ack_recv_valid; int ack_next_valid; int ack_required; void* ack_next; void* ack_recv; } ;
struct rds_connection {int /*<<< orphan*/  c_laddr; int /*<<< orphan*/  c_faddr; struct rds_iw_connection* c_transport_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  f_item; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  KM_SOFTIRQ0 ; 
 int RDS_FLAG_ACK_REQUIRED ; 
 scalar_t__ RDS_FLAG_CONG_BITMAP ; 
 struct rds_iw_recv_work* RDS_FRAG_SIZE ; 
 struct rds_iw_recv_work* be32_to_cpu (scalar_t__) ; 
 void* be64_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct rds_header*,struct rds_header*,int) ; 
 int /*<<< orphan*/  rds_inc_put (TYPE_1__*) ; 
 int /*<<< orphan*/  rds_iw_cong_recv (struct rds_connection*,struct rds_iw_incoming*) ; 
 int /*<<< orphan*/  rds_iw_conn_error (struct rds_connection*,char*,...) ; 
 int /*<<< orphan*/  rds_iw_frag_drop_page (TYPE_2__*) ; 
 int /*<<< orphan*/  rds_iw_send_add_credits (struct rds_connection*,scalar_t__) ; 
 int /*<<< orphan*/  rds_iw_stats_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_message_verify_checksum (struct rds_header*) ; 
 int /*<<< orphan*/  rds_recv_incoming (struct rds_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_stats_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdsdebug (char*,struct rds_iw_connection*,struct rds_iw_incoming*,struct rds_iw_recv_work*,int) ; 
 int /*<<< orphan*/  s_iw_ack_received ; 
 int /*<<< orphan*/  s_recv_ack_required ; 
 int /*<<< orphan*/  s_recv_drop_bad_checksum ; 

__attribute__((used)) static void rds_iw_process_recv(struct rds_connection *conn,
				struct rds_iw_recv_work *recv, u32 byte_len,
				struct rds_iw_ack_state *state)
{
	struct rds_iw_connection *ic = conn->c_transport_data;
	struct rds_iw_incoming *iwinc = ic->i_iwinc;
	struct rds_header *ihdr, *hdr;

	/* XXX shut down the connection if port 0,0 are seen? */

	rdsdebug("ic %p iwinc %p recv %p byte len %u\n", ic, iwinc, recv,
		 byte_len);

	if (byte_len < sizeof(struct rds_header)) {
		rds_iw_conn_error(conn, "incoming message "
		       "from %pI4 didn't include a "
		       "header, disconnecting and "
		       "reconnecting\n",
		       &conn->c_faddr);
		return;
	}
	byte_len -= sizeof(struct rds_header);

	ihdr = &ic->i_recv_hdrs[recv - ic->i_recvs];

	/* Validate the checksum. */
	if (!rds_message_verify_checksum(ihdr)) {
		rds_iw_conn_error(conn, "incoming message "
		       "from %pI4 has corrupted header - "
		       "forcing a reconnect\n",
		       &conn->c_faddr);
		rds_stats_inc(s_recv_drop_bad_checksum);
		return;
	}

	/* Process the ACK sequence which comes with every packet */
	state->ack_recv = be64_to_cpu(ihdr->h_ack);
	state->ack_recv_valid = 1;

	/* Process the credits update if there was one */
	if (ihdr->h_credit)
		rds_iw_send_add_credits(conn, ihdr->h_credit);

	if (ihdr->h_sport == 0 && ihdr->h_dport == 0 && byte_len == 0) {
		/* This is an ACK-only packet. The fact that it gets
		 * special treatment here is that historically, ACKs
		 * were rather special beasts.
		 */
		rds_iw_stats_inc(s_iw_ack_received);

		/*
		 * Usually the frags make their way on to incs and are then freed as
		 * the inc is freed.  We don't go that route, so we have to drop the
		 * page ref ourselves.  We can't just leave the page on the recv
		 * because that confuses the dma mapping of pages and each recv's use
		 * of a partial page.  We can leave the frag, though, it will be
		 * reused.
		 *
		 * FIXME: Fold this into the code path below.
		 */
		rds_iw_frag_drop_page(recv->r_frag);
		return;
	}

	/*
	 * If we don't already have an inc on the connection then this
	 * fragment has a header and starts a message.. copy its header
	 * into the inc and save the inc so we can hang upcoming fragments
	 * off its list.
	 */
	if (!iwinc) {
		iwinc = recv->r_iwinc;
		recv->r_iwinc = NULL;
		ic->i_iwinc = iwinc;

		hdr = &iwinc->ii_inc.i_hdr;
		memcpy(hdr, ihdr, sizeof(*hdr));
		ic->i_recv_data_rem = be32_to_cpu(hdr->h_len);

		rdsdebug("ic %p iwinc %p rem %u flag 0x%x\n", ic, iwinc,
			 ic->i_recv_data_rem, hdr->h_flags);
	} else {
		hdr = &iwinc->ii_inc.i_hdr;
		/* We can't just use memcmp here; fragments of a
		 * single message may carry different ACKs */
		if (hdr->h_sequence != ihdr->h_sequence
		 || hdr->h_len != ihdr->h_len
		 || hdr->h_sport != ihdr->h_sport
		 || hdr->h_dport != ihdr->h_dport) {
			rds_iw_conn_error(conn,
				"fragment header mismatch; forcing reconnect\n");
			return;
		}
	}

	list_add_tail(&recv->r_frag->f_item, &iwinc->ii_frags);
	recv->r_frag = NULL;

	if (ic->i_recv_data_rem > RDS_FRAG_SIZE)
		ic->i_recv_data_rem -= RDS_FRAG_SIZE;
	else {
		ic->i_recv_data_rem = 0;
		ic->i_iwinc = NULL;

		if (iwinc->ii_inc.i_hdr.h_flags == RDS_FLAG_CONG_BITMAP)
			rds_iw_cong_recv(conn, iwinc);
		else {
			rds_recv_incoming(conn, conn->c_faddr, conn->c_laddr,
					  &iwinc->ii_inc, GFP_ATOMIC,
					  KM_SOFTIRQ0);
			state->ack_next = be64_to_cpu(hdr->h_sequence);
			state->ack_next_valid = 1;
		}

		/* Evaluate the ACK_REQUIRED flag *after* we received
		 * the complete frame, and after bumping the next_rx
		 * sequence. */
		if (hdr->h_flags & RDS_FLAG_ACK_REQUIRED) {
			rds_stats_inc(s_recv_ack_required);
			state->ack_required = 1;
		}

		rds_inc_put(&iwinc->ii_inc);
	}
}