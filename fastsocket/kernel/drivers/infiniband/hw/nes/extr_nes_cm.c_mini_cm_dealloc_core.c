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
struct nes_cm_core {int /*<<< orphan*/  disconn_wq; int /*<<< orphan*/  event_wq; int /*<<< orphan*/  tcp_timer; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NES_DBG_CM ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nes_cm_core*) ; 
 int /*<<< orphan*/  nes_debug (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mini_cm_dealloc_core(struct nes_cm_core *cm_core)
{
	nes_debug(NES_DBG_CM, "De-Alloc CM Core (%p)\n", cm_core);

	if (!cm_core)
		return -EINVAL;

	barrier();

	if (timer_pending(&cm_core->tcp_timer))
		del_timer(&cm_core->tcp_timer);

	destroy_workqueue(cm_core->event_wq);
	destroy_workqueue(cm_core->disconn_wq);
	nes_debug(NES_DBG_CM, "\n");
	kfree(cm_core);

	return 0;
}