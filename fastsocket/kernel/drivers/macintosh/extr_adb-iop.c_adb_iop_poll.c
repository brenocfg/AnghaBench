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
 scalar_t__ ADB_IOP ; 
 int /*<<< orphan*/  adb_iop_start () ; 
 scalar_t__ adb_iop_state ; 
 scalar_t__ idle ; 
 int /*<<< orphan*/  iop_ism_irq (int /*<<< orphan*/ ,void*) ; 

void adb_iop_poll(void)
{
	if (adb_iop_state == idle) adb_iop_start();
	iop_ism_irq(0, (void *) ADB_IOP);
}