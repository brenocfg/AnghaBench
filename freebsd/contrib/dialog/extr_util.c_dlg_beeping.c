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
struct TYPE_2__ {scalar_t__ beep_signal; } ;

/* Variables and functions */
 int /*<<< orphan*/  beep () ; 
 TYPE_1__ dialog_vars ; 

void
dlg_beeping(void)
{
    if (dialog_vars.beep_signal) {
	(void) beep();
	dialog_vars.beep_signal = 0;
    }
}