#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
typedef  size_t u_char ;
struct TYPE_16__ {scalar_t__ fifos; int /*<<< orphan*/  bswapped; } ;
struct TYPE_17__ {TYPE_4__ hfcpci; } ;
struct IsdnCardState {int debug; TYPE_5__ hw; } ;
struct BCState {scalar_t__ mode; int tx_cnt; int ackcnt; int /*<<< orphan*/  Flag; TYPE_9__* tx_skb; int /*<<< orphan*/  aclock; TYPE_2__* st; scalar_t__ channel; int /*<<< orphan*/  squeue; struct IsdnCardState* cs; } ;
struct TYPE_20__ {size_t f1; int f2; TYPE_6__* za; } ;
struct TYPE_15__ {size_t* txdat_b2; size_t* txdat_b1; TYPE_8__ txbz_b1; TYPE_8__ txbz_b2; } ;
struct TYPE_19__ {TYPE_3__ b_chans; } ;
typedef  TYPE_7__ fifo_area ;
typedef  TYPE_8__ bzfifo_type ;
struct TYPE_21__ {int len; size_t* data; scalar_t__ pkt_type; } ;
struct TYPE_18__ {unsigned short z1; int z2; } ;
struct TYPE_13__ {int /*<<< orphan*/  flag; } ;
struct TYPE_14__ {TYPE_1__ lli; } ;
struct TYPE_12__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BC_FLG_BUSY ; 
 int /*<<< orphan*/  B_ACKPENDING ; 
 int B_FIFO_SIZE ; 
 int B_SUB_VAL ; 
 int /*<<< orphan*/  FLG_LLI_L1WAKEUP ; 
 int HFCPCI_BTRANS_THRESHOLD ; 
 int L1_DEB_HSCX ; 
 scalar_t__ L1_MODE_TRANS ; 
 size_t MAX_B_FRAMES ; 
 scalar_t__ PACKET_NOACK ; 
 TYPE_11__* current ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*,...) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (TYPE_9__*) ; 
 int /*<<< orphan*/  memcpy (size_t*,size_t*,int) ; 
 int /*<<< orphan*/  schedule_event (struct BCState*,int /*<<< orphan*/ ) ; 
 TYPE_9__* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
hfcpci_fill_fifo(struct BCState *bcs)
{
	struct IsdnCardState *cs = bcs->cs;
	int maxlen, fcnt;
	int count, new_z1;
	bzfifo_type *bz;
	u_char *bdata;
	u_char new_f1, *src, *dst;
	unsigned short *z1t, *z2t;

	if (!bcs->tx_skb)
		return;
	if (bcs->tx_skb->len <= 0)
		return;

	if ((bcs->channel) && (!cs->hw.hfcpci.bswapped)) {
		bz = &((fifo_area *) (cs->hw.hfcpci.fifos))->b_chans.txbz_b2;
		bdata = ((fifo_area *) (cs->hw.hfcpci.fifos))->b_chans.txdat_b2;
	} else {
		bz = &((fifo_area *) (cs->hw.hfcpci.fifos))->b_chans.txbz_b1;
		bdata = ((fifo_area *) (cs->hw.hfcpci.fifos))->b_chans.txdat_b1;
	}

	if (bcs->mode == L1_MODE_TRANS) {
		z1t = &bz->za[MAX_B_FRAMES].z1;
		z2t = z1t + 1;
		if (cs->debug & L1_DEB_HSCX)
			debugl1(cs, "hfcpci_fill_fifo_trans %d z1(%x) z2(%x)",
				bcs->channel, *z1t, *z2t);
		fcnt = *z2t - *z1t;
		if (fcnt <= 0)
			fcnt += B_FIFO_SIZE;	/* fcnt contains available bytes in fifo */
		fcnt = B_FIFO_SIZE - fcnt;	/* remaining bytes to send */

		while ((fcnt < 2 * HFCPCI_BTRANS_THRESHOLD) && (bcs->tx_skb)) {
			if (bcs->tx_skb->len < B_FIFO_SIZE - fcnt) {
				/* data is suitable for fifo */
				count = bcs->tx_skb->len;

				new_z1 = *z1t + count;	/* new buffer Position */
				if (new_z1 >= (B_FIFO_SIZE + B_SUB_VAL))
					new_z1 -= B_FIFO_SIZE;	/* buffer wrap */
				src = bcs->tx_skb->data;	/* source pointer */
				dst = bdata + (*z1t - B_SUB_VAL);
				maxlen = (B_FIFO_SIZE + B_SUB_VAL) - *z1t;	/* end of fifo */
				if (maxlen > count)
					maxlen = count;		/* limit size */
				memcpy(dst, src, maxlen);	/* first copy */

				count -= maxlen;	/* remaining bytes */
				if (count) {
					dst = bdata;	/* start of buffer */
					src += maxlen;	/* new position */
					memcpy(dst, src, count);
				}
				bcs->tx_cnt -= bcs->tx_skb->len;
				fcnt += bcs->tx_skb->len;
				*z1t = new_z1;	/* now send data */
			} else if (cs->debug & L1_DEB_HSCX)
				debugl1(cs, "hfcpci_fill_fifo_trans %d frame length %d discarded",
					bcs->channel, bcs->tx_skb->len);

			if (test_bit(FLG_LLI_L1WAKEUP,&bcs->st->lli.flag) &&
				(PACKET_NOACK != bcs->tx_skb->pkt_type)) {
				u_long	flags;
				spin_lock_irqsave(&bcs->aclock, flags);
				bcs->ackcnt += bcs->tx_skb->len;
				spin_unlock_irqrestore(&bcs->aclock, flags);
				schedule_event(bcs, B_ACKPENDING);
			}

			dev_kfree_skb_any(bcs->tx_skb);
			bcs->tx_skb = skb_dequeue(&bcs->squeue);	/* fetch next data */
		}
		test_and_clear_bit(BC_FLG_BUSY, &bcs->Flag);
		return;
	}
	if (cs->debug & L1_DEB_HSCX)
		debugl1(cs, "hfcpci_fill_fifo_hdlc %d f1(%d) f2(%d) z1(f1)(%x)",
			bcs->channel, bz->f1, bz->f2,
			bz->za[bz->f1].z1);

	fcnt = bz->f1 - bz->f2;	/* frame count actually buffered */
	if (fcnt < 0)
		fcnt += (MAX_B_FRAMES + 1);	/* if wrap around */
	if (fcnt > (MAX_B_FRAMES - 1)) {
		if (cs->debug & L1_DEB_HSCX)
			debugl1(cs, "hfcpci_fill_Bfifo more as 14 frames");
		return;
	}
	/* now determine free bytes in FIFO buffer */
	count = bz->za[bz->f2].z2 - bz->za[bz->f1].z1 - 1;
	if (count <= 0)
		count += B_FIFO_SIZE;	/* count now contains available bytes */

	if (cs->debug & L1_DEB_HSCX)
		debugl1(cs, "hfcpci_fill_fifo %d count(%ld/%d),%lx",
			bcs->channel, bcs->tx_skb->len,
			count, current->state);

	if (count < bcs->tx_skb->len) {
		if (cs->debug & L1_DEB_HSCX)
			debugl1(cs, "hfcpci_fill_fifo no fifo mem");
		return;
	}
	count = bcs->tx_skb->len;	/* get frame len */
	new_z1 = bz->za[bz->f1].z1 + count;	/* new buffer Position */
	if (new_z1 >= (B_FIFO_SIZE + B_SUB_VAL))
		new_z1 -= B_FIFO_SIZE;	/* buffer wrap */

	new_f1 = ((bz->f1 + 1) & MAX_B_FRAMES);
	src = bcs->tx_skb->data;	/* source pointer */
	dst = bdata + (bz->za[bz->f1].z1 - B_SUB_VAL);
	maxlen = (B_FIFO_SIZE + B_SUB_VAL) - bz->za[bz->f1].z1;		/* end fifo */
	if (maxlen > count)
		maxlen = count;	/* limit size */
	memcpy(dst, src, maxlen);	/* first copy */

	count -= maxlen;	/* remaining bytes */
	if (count) {
		dst = bdata;	/* start of buffer */
		src += maxlen;	/* new position */
		memcpy(dst, src, count);
	}
	bcs->tx_cnt -= bcs->tx_skb->len;
	if (test_bit(FLG_LLI_L1WAKEUP,&bcs->st->lli.flag) &&
		(PACKET_NOACK != bcs->tx_skb->pkt_type)) {
		u_long	flags;
		spin_lock_irqsave(&bcs->aclock, flags);
		bcs->ackcnt += bcs->tx_skb->len;
		spin_unlock_irqrestore(&bcs->aclock, flags);
		schedule_event(bcs, B_ACKPENDING);
	}

	bz->za[new_f1].z1 = new_z1;	/* for next buffer */
	bz->f1 = new_f1;	/* next frame */

	dev_kfree_skb_any(bcs->tx_skb);
	bcs->tx_skb = NULL;
	test_and_clear_bit(BC_FLG_BUSY, &bcs->Flag);
}