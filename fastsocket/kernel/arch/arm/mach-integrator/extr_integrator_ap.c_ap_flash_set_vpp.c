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
 int /*<<< orphan*/  INTEGRATOR_SC_CTRL_nFLVPPEN ; 
 unsigned long SC_CTRLC ; 
 unsigned long SC_CTRLS ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void ap_flash_set_vpp(int on)
{
	unsigned long reg = on ? SC_CTRLS : SC_CTRLC;

	writel(INTEGRATOR_SC_CTRL_nFLVPPEN, reg);
}