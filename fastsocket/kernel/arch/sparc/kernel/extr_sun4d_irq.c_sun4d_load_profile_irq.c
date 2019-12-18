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
 int /*<<< orphan*/  bw_set_prof_limit (int,unsigned int) ; 

__attribute__((used)) static void sun4d_load_profile_irq(int cpu, unsigned int limit)
{
	bw_set_prof_limit(cpu, limit);
}