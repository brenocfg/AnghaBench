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
struct TYPE_2__ {int /*<<< orphan*/  itr; } ;
struct ixgbevf_q_vector {int itr; TYPE_1__ tx; TYPE_1__ rx; } ;

/* Variables and functions */
 int IXGBE_100K_ITR ; 
 int IXGBE_20K_ITR ; 
 int IXGBE_8K_ITR ; 
#define  bulk_latency 130 
 int /*<<< orphan*/  ixgbevf_update_itr (struct ixgbevf_q_vector*,TYPE_1__*) ; 
 int /*<<< orphan*/  ixgbevf_write_eitr (struct ixgbevf_q_vector*) ; 
#define  low_latency 129 
#define  lowest_latency 128 
 int max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ixgbevf_set_itr(struct ixgbevf_q_vector *q_vector)
{
	u32 new_itr = q_vector->itr;
	u8 current_itr;

	ixgbevf_update_itr(q_vector, &q_vector->tx);
	ixgbevf_update_itr(q_vector, &q_vector->rx);

	current_itr = max(q_vector->rx.itr, q_vector->tx.itr);

	switch (current_itr) {
	/* counts and packets in update_itr are dependent on these numbers */
	case lowest_latency:
		new_itr = IXGBE_100K_ITR;
		break;
	case low_latency:
		new_itr = IXGBE_20K_ITR;
		break;
	case bulk_latency:
	default:
		new_itr = IXGBE_8K_ITR;
		break;
	}

	if (new_itr != q_vector->itr) {
		/* do an exponential smoothing */
		new_itr = (10 * new_itr * q_vector->itr) /
			  ((9 * new_itr) + q_vector->itr);

		/* save the algorithm value here */
		q_vector->itr = new_itr;

		ixgbevf_write_eitr(q_vector);
	}
}