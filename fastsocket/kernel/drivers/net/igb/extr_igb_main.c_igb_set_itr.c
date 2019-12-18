#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {int itr; scalar_t__ ring; } ;
struct igb_q_vector {int itr_val; int set_itr; TYPE_1__ rx; TYPE_1__ tx; struct igb_adapter* adapter; } ;
struct igb_adapter {scalar_t__ link_speed; int rx_itr_setting; int tx_itr_setting; } ;

/* Variables and functions */
 int IGB_20K_ITR ; 
 int IGB_4K_ITR ; 
 int IGB_70K_ITR ; 
 scalar_t__ SPEED_1000 ; 
#define  bulk_latency 130 
 int /*<<< orphan*/  igb_update_itr (struct igb_q_vector*,TYPE_1__*) ; 
#define  low_latency 129 
#define  lowest_latency 128 
 int max (int,int) ; 

__attribute__((used)) static void igb_set_itr(struct igb_q_vector *q_vector)
{
	struct igb_adapter *adapter = q_vector->adapter;
	u32 new_itr = q_vector->itr_val;
	u8 current_itr = 0;

	/* for non-gigabit speeds, just fix the interrupt rate at 4000 */
	if (adapter->link_speed != SPEED_1000) {
		current_itr = 0;
		new_itr = IGB_4K_ITR;
		goto set_itr_now;
	}

	igb_update_itr(q_vector, &q_vector->tx);
	igb_update_itr(q_vector, &q_vector->rx);

	current_itr = max(q_vector->rx.itr, q_vector->tx.itr);

	/* conservative mode (itr 3) eliminates the lowest_latency setting */
	if (current_itr == lowest_latency &&
	    ((q_vector->rx.ring && adapter->rx_itr_setting == 3) ||
	     (!q_vector->rx.ring && adapter->tx_itr_setting == 3)))
		current_itr = low_latency;

	switch (current_itr) {
	/* counts and packets in update_itr are dependent on these numbers */
	case lowest_latency:
		new_itr = IGB_70K_ITR; /* 70,000 ints/sec */
		break;
	case low_latency:
		new_itr = IGB_20K_ITR; /* 20,000 ints/sec */
		break;
	case bulk_latency:
		new_itr = IGB_4K_ITR;  /* 4,000 ints/sec */
		break;
	default:
		break;
	}

set_itr_now:
	if (new_itr != q_vector->itr_val) {
		/* this attempts to bias the interrupt rate towards Bulk
		 * by adding intermediate steps when interrupt rate is
		 * increasing
		 */
		new_itr = new_itr > q_vector->itr_val ?
			  max((new_itr * q_vector->itr_val) /
			  (new_itr + (q_vector->itr_val >> 2)),
			  new_itr) : new_itr;
		/* Don't write the value here; it resets the adapter's
		 * internal timer, and causes us to delay far longer than
		 * we should between interrupts.  Instead, we write the ITR
		 * value at the beginning of the next interrupt so the timing
		 * ends up being correct.
		 */
		q_vector->itr_val = new_itr;
		q_vector->set_itr = 1;
	}
}