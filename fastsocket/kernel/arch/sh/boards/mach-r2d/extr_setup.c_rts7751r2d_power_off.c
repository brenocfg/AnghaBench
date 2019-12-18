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
 int /*<<< orphan*/  PA_POWOFF ; 
 int /*<<< orphan*/  ctrl_outw (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rts7751r2d_power_off(void)
{
	ctrl_outw(0x0001, PA_POWOFF);
}