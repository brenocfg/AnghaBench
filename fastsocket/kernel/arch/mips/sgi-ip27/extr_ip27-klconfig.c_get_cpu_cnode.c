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
typedef  int /*<<< orphan*/  cpuid_t ;
typedef  int /*<<< orphan*/  cnodeid_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPUID_TO_COMPACT_NODEID (int /*<<< orphan*/ ) ; 

cnodeid_t get_cpu_cnode(cpuid_t cpu)
{
	return CPUID_TO_COMPACT_NODEID(cpu);
}