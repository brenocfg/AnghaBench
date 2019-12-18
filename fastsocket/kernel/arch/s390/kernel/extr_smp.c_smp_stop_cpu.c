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
 int /*<<< orphan*/  cpu_relax () ; 
 scalar_t__ signal_processor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sigp_busy ; 
 int /*<<< orphan*/  sigp_stop ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static void smp_stop_cpu(void)
{
	while (signal_processor(smp_processor_id(), sigp_stop) == sigp_busy)
		cpu_relax();
}