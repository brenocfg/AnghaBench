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
struct cpuinfo_x86 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_init_cmci () ; 
 int /*<<< orphan*/  intel_init_thermal (struct cpuinfo_x86*) ; 

void mce_intel_feature_init(struct cpuinfo_x86 *c)
{
	intel_init_thermal(c);
	intel_init_cmci();
}