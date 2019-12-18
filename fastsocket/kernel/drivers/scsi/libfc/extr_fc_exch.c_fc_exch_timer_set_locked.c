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
struct fc_exch {int state; int /*<<< orphan*/  timeout_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_EXCH_DBG (struct fc_exch*,char*) ; 
 int FC_EX_DONE ; 
 int FC_EX_RST_CLEANUP ; 
 int /*<<< orphan*/  fc_exch_hold (struct fc_exch*) ; 
 int /*<<< orphan*/  fc_exch_workqueue ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned int) ; 
 scalar_t__ queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void fc_exch_timer_set_locked(struct fc_exch *ep,
					    unsigned int timer_msec)
{
	if (ep->state & (FC_EX_RST_CLEANUP | FC_EX_DONE))
		return;

	FC_EXCH_DBG(ep, "Exchange timer armed\n");

	if (queue_delayed_work(fc_exch_workqueue, &ep->timeout_work,
			       msecs_to_jiffies(timer_msec)))
		fc_exch_hold(ep);		/* hold for timer */
}