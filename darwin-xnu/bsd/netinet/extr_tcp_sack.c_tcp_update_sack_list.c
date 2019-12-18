#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  void* tcp_seq ;
struct tcpcb {int rcv_numsacks; void* rcv_nxt; int t_flags; scalar_t__ acc_iaj; struct sackblk* sackblks; } ;
struct sackblk {void* start; void* end; } ;

/* Variables and functions */
 int MAX_SACK_BLKS ; 
 scalar_t__ SEQ_GEQ (void*,void*) ; 
 scalar_t__ SEQ_GT (void*,void*) ; 
 scalar_t__ SEQ_LEQ (void*,void*) ; 
 scalar_t__ SEQ_LT (void*,void*) ; 
 int TF_STRETCHACK ; 
 int /*<<< orphan*/  bcopy (struct sackblk*,struct sackblk*,int) ; 
 int /*<<< orphan*/  reset_acc_iaj (struct tcpcb*) ; 
 int /*<<< orphan*/  tcp_reset_stretch_ack (struct tcpcb*) ; 

void
tcp_update_sack_list(struct tcpcb *tp, tcp_seq rcv_start, tcp_seq rcv_end)
{
	/*
	 * First reported block MUST be the most recent one.  Subsequent
	 * blocks SHOULD be in the order in which they arrived at the
	 * receiver.  These two conditions make the implementation fully
	 * compliant with RFC 2018.
	 */
	struct sackblk head_blk, saved_blks[MAX_SACK_BLKS];
	int num_head, num_saved, i;

	/* SACK block for the received segment. */
	head_blk.start = rcv_start;
	head_blk.end = rcv_end;

	/*
	 * Merge updated SACK blocks into head_blk, and
	 * save unchanged SACK blocks into saved_blks[].
	 * num_saved will have the number of the saved SACK blocks.
	 */
	num_saved = 0;
	for (i = 0; i < tp->rcv_numsacks; i++) {
		tcp_seq start = tp->sackblks[i].start;
		tcp_seq end = tp->sackblks[i].end;
		if (SEQ_GEQ(start, end) || SEQ_LEQ(start, tp->rcv_nxt)) {
			/*
			 * Discard this SACK block.
			 */
		} else if (SEQ_LEQ(head_blk.start, end) &&
			   SEQ_GEQ(head_blk.end, start)) {
			/*
			 * Merge this SACK block into head_blk.
			 * This SACK block itself will be discarded.
			 */
			if (SEQ_GT(head_blk.start, start))
				head_blk.start = start;
			if (SEQ_LT(head_blk.end, end))
				head_blk.end = end;
		} else {
			/*
			 * Save this SACK block.
			 */
			saved_blks[num_saved].start = start;
			saved_blks[num_saved].end = end;
			num_saved++;
		}
	}

	/*
	 * Update SACK list in tp->sackblks[].
	 */
	num_head = 0;
	if (SEQ_GT(head_blk.start, tp->rcv_nxt)) {
		/*
		 * The received data segment is an out-of-order segment.
		 * Put head_blk at the top of SACK list.
		 */
		tp->sackblks[0] = head_blk;
		num_head = 1;
		/*
		 * If the number of saved SACK blocks exceeds its limit,
		 * discard the last SACK block.
		 */
		if (num_saved >= MAX_SACK_BLKS)
			num_saved--;
	}
	if (num_saved > 0) {
		/*
		 * Copy the saved SACK blocks back.
		 */
		bcopy(saved_blks, &tp->sackblks[num_head],
		      sizeof(struct sackblk) * num_saved);
	}

	/* Save the number of SACK blocks. */
	tp->rcv_numsacks = num_head + num_saved;

	/* If we are requesting SACK recovery, reset the stretch-ack state
	 * so that connection will generate more acks after recovery and
	 * sender's cwnd will open.
	 */
	if ((tp->t_flags & TF_STRETCHACK) != 0 && tp->rcv_numsacks > 0)
		tcp_reset_stretch_ack(tp);

#if TRAFFIC_MGT
	if (tp->acc_iaj > 0 && tp->rcv_numsacks > 0) 
		reset_acc_iaj(tp);
#endif /* TRAFFIC_MGT */
}