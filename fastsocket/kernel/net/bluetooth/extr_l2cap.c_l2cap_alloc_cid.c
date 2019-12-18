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
typedef  scalar_t__ u16 ;
struct l2cap_chan_list {int dummy; } ;

/* Variables and functions */
 scalar_t__ L2CAP_CID_DYN_END ; 
 scalar_t__ L2CAP_CID_DYN_START ; 
 int /*<<< orphan*/  __l2cap_get_chan_by_scid (struct l2cap_chan_list*,scalar_t__) ; 

__attribute__((used)) static u16 l2cap_alloc_cid(struct l2cap_chan_list *l)
{
	u16 cid = L2CAP_CID_DYN_START;

	for (; cid < L2CAP_CID_DYN_END; cid++) {
		if (!__l2cap_get_chan_by_scid(l, cid))
			return cid;
	}

	return 0;
}