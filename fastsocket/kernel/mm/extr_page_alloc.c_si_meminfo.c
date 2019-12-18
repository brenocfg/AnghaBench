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
struct sysinfo {int /*<<< orphan*/  mem_unit; int /*<<< orphan*/  freehigh; int /*<<< orphan*/  totalhigh; int /*<<< orphan*/  bufferram; int /*<<< orphan*/  freeram; scalar_t__ sharedram; int /*<<< orphan*/  totalram; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_FREE_PAGES ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  global_page_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nr_blockdev_pages () ; 
 int /*<<< orphan*/  nr_free_highpages () ; 
 int /*<<< orphan*/  totalhigh_pages ; 
 int /*<<< orphan*/  totalram_pages ; 

void si_meminfo(struct sysinfo *val)
{
	val->totalram = totalram_pages;
	val->sharedram = 0;
	val->freeram = global_page_state(NR_FREE_PAGES);
	val->bufferram = nr_blockdev_pages();
	val->totalhigh = totalhigh_pages;
	val->freehigh = nr_free_highpages();
	val->mem_unit = PAGE_SIZE;
}