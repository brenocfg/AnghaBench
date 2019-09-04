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
struct meminfo {int /*<<< orphan*/  purgeable_volatile_compressed; int /*<<< orphan*/  purgeable_volatile; int /*<<< orphan*/  phys_footprint; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_DATA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PERF_MI_DATA ; 

void
kperf_meminfo_log(struct meminfo *mi)
{
	BUF_DATA(PERF_MI_DATA, mi->phys_footprint, mi->purgeable_volatile,
	         mi->purgeable_volatile_compressed);
}