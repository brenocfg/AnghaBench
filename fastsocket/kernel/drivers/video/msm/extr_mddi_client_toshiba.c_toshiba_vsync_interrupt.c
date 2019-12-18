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
struct panel_info {int toshiba_got_int; TYPE_1__* toshiba_callback; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* func ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  toshiba_vsync_wait ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

irqreturn_t toshiba_vsync_interrupt(int irq, void *data)
{
	struct panel_info *panel = data;

	panel->toshiba_got_int = 1;
	if (panel->toshiba_callback) {
		panel->toshiba_callback->func(panel->toshiba_callback);
		panel->toshiba_callback = 0;
	}
	wake_up(&toshiba_vsync_wait);
	return IRQ_HANDLED;
}