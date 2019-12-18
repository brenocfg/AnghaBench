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
struct hlist_head {int dummy; } ;
struct dev_rcv_lists {struct hlist_head* rx; struct hlist_head* rx_sff; } ;
typedef  int canid_t ;

/* Variables and functions */
 int CAN_EFF_FLAG ; 
 int CAN_EFF_MASK ; 
 int CAN_EFF_RTR_FLAGS ; 
 int CAN_ERR_FLAG ; 
 int CAN_ERR_MASK ; 
 int CAN_INV_FILTER ; 
 int CAN_RTR_FLAG ; 
 int CAN_SFF_MASK ; 
 size_t RX_ALL ; 
 size_t RX_EFF ; 
 size_t RX_ERR ; 
 size_t RX_FIL ; 
 size_t RX_INV ; 

__attribute__((used)) static struct hlist_head *find_rcv_list(canid_t *can_id, canid_t *mask,
					struct dev_rcv_lists *d)
{
	canid_t inv = *can_id & CAN_INV_FILTER; /* save flag before masking */

	/* filter for error frames in extra filterlist */
	if (*mask & CAN_ERR_FLAG) {
		/* clear CAN_ERR_FLAG in filter entry */
		*mask &= CAN_ERR_MASK;
		return &d->rx[RX_ERR];
	}

	/* with cleared CAN_ERR_FLAG we have a simple mask/value filterpair */

#define CAN_EFF_RTR_FLAGS (CAN_EFF_FLAG | CAN_RTR_FLAG)

	/* ensure valid values in can_mask for 'SFF only' frame filtering */
	if ((*mask & CAN_EFF_FLAG) && !(*can_id & CAN_EFF_FLAG))
		*mask &= (CAN_SFF_MASK | CAN_EFF_RTR_FLAGS);

	/* reduce condition testing at receive time */
	*can_id &= *mask;

	/* inverse can_id/can_mask filter */
	if (inv)
		return &d->rx[RX_INV];

	/* mask == 0 => no condition testing at receive time */
	if (!(*mask))
		return &d->rx[RX_ALL];

	/* extra filterlists for the subscription of a single non-RTR can_id */
	if (((*mask & CAN_EFF_RTR_FLAGS) == CAN_EFF_RTR_FLAGS)
	    && !(*can_id & CAN_RTR_FLAG)) {

		if (*can_id & CAN_EFF_FLAG) {
			if (*mask == (CAN_EFF_MASK | CAN_EFF_RTR_FLAGS)) {
				/* RFC: a future use-case for hash-tables? */
				return &d->rx[RX_EFF];
			}
		} else {
			if (*mask == (CAN_SFF_MASK | CAN_EFF_RTR_FLAGS))
				return &d->rx_sff[*can_id];
		}
	}

	/* default: filter via can_id/can_mask */
	return &d->rx[RX_FIL];
}