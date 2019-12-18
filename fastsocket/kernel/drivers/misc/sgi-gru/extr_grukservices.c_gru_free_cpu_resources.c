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
 int /*<<< orphan*/  gru_unlock_kernel_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  uv_numa_blade_id () ; 

__attribute__((used)) static void gru_free_cpu_resources(void *cb, void *dsr)
{
	gru_unlock_kernel_context(uv_numa_blade_id());
	preempt_enable();
}