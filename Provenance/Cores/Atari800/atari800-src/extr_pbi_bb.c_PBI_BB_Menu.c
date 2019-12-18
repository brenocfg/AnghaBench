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

/* Variables and functions */
 int /*<<< orphan*/  BB_BUTTON_IRQ_MASK ; 
 int /*<<< orphan*/  CPU_GenerateIRQ () ; 
 int /*<<< orphan*/  D (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  PBI_BB_enabled ; 
 int /*<<< orphan*/  PBI_IRQ ; 
 scalar_t__ TRUE ; 
 scalar_t__ buttondown ; 
 int /*<<< orphan*/  printf (char*) ; 

void PBI_BB_Menu(void)
{
	if (!PBI_BB_enabled) return;
	if (buttondown == FALSE) {
		D(printf("blackbox button down interrupt generated\n"));
		CPU_GenerateIRQ();
		PBI_IRQ |= BB_BUTTON_IRQ_MASK;
		buttondown = TRUE;
	}
}