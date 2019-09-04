#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  cpu_monotonic; } ;
typedef  TYPE_1__ cpu_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  mt_mtc_update_count (int /*<<< orphan*/ *,unsigned int) ; 

uint64_t
mt_cpu_update_count(cpu_data_t *cpu, unsigned int ctr)
{
	return mt_mtc_update_count(&cpu->cpu_monotonic, ctr);
}