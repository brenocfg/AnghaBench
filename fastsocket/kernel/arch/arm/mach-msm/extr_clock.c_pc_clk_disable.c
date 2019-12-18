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
 int /*<<< orphan*/  PCOM_CLKCTL_RPC_DISABLE ; 
 int /*<<< orphan*/  msm_proc_comm (int /*<<< orphan*/ ,unsigned int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void pc_clk_disable(unsigned id)
{
	msm_proc_comm(PCOM_CLKCTL_RPC_DISABLE, &id, NULL);
}