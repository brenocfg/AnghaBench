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
struct TYPE_2__ {int /*<<< orphan*/  (* event ) (int /*<<< orphan*/ ,unsigned int) ;} ;
struct ldc_channel {int /*<<< orphan*/  event_arg; TYPE_1__ cfg; } ;

/* Variables and functions */
 unsigned int LDC_EVENT_DATA_READY ; 
 unsigned int LDC_EVENT_RESET ; 
 unsigned int LDC_EVENT_UP ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void send_events(struct ldc_channel *lp, unsigned int event_mask)
{
	if (event_mask & LDC_EVENT_RESET)
		lp->cfg.event(lp->event_arg, LDC_EVENT_RESET);
	if (event_mask & LDC_EVENT_UP)
		lp->cfg.event(lp->event_arg, LDC_EVENT_UP);
	if (event_mask & LDC_EVENT_DATA_READY)
		lp->cfg.event(lp->event_arg, LDC_EVENT_DATA_READY);
}