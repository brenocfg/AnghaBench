#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  tqueue; int /*<<< orphan*/  super_tx_queue; int /*<<< orphan*/  frame_cnt; } ;
typedef  TYPE_1__ isdn_net_local ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isdn_net_device_busy (TYPE_1__*) ; 
 int /*<<< orphan*/  isdn_net_device_wake_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline__ void isdn_net_dec_frame_cnt(isdn_net_local *lp)
{
	atomic_dec(&lp->frame_cnt);

	if (!(isdn_net_device_busy(lp))) {
		if (!skb_queue_empty(&lp->super_tx_queue)) {
			schedule_work(&lp->tqueue);
		} else {
			isdn_net_device_wake_queue(lp);
		}
       }                                                                      
}