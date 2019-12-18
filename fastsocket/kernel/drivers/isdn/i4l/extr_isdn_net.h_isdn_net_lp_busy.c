#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  frame_cnt; } ;
typedef  TYPE_1__ isdn_net_local ;

/* Variables and functions */
 scalar_t__ ISDN_NET_MAX_QUEUE_LENGTH ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline__ int isdn_net_lp_busy(isdn_net_local *lp)
{
	if (atomic_read(&lp->frame_cnt) < ISDN_NET_MAX_QUEUE_LENGTH)
		return 0;
	else 
		return 1;
}