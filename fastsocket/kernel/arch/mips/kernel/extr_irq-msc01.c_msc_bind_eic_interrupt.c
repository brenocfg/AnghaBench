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
 int /*<<< orphan*/  MSC01_IC_RAMW ; 
 int MSC01_IC_RAMW_ADDR_SHF ; 
 int MSC01_IC_RAMW_DATA_SHF ; 
 int /*<<< orphan*/  MSCIC_WRITE (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void msc_bind_eic_interrupt(int irq, int set)
{
	MSCIC_WRITE(MSC01_IC_RAMW,
		    (irq<<MSC01_IC_RAMW_ADDR_SHF) | (set<<MSC01_IC_RAMW_DATA_SHF));
}