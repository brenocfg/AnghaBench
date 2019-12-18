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
 int PAGE_SIZE ; 
 int SRMMU_MAX_NOCACHE_PAGES ; 
 int SRMMU_MIN_NOCACHE_PAGES ; 
 unsigned long SRMMU_NOCACHE_ALCRATIO ; 
 scalar_t__ SRMMU_NOCACHE_VADDR ; 
 int probe_memory () ; 
 scalar_t__ srmmu_nocache_end ; 
 int srmmu_nocache_size ; 

__attribute__((used)) static void srmmu_nocache_calcsize(void)
{
	unsigned long sysmemavail = probe_memory() / 1024;
	int srmmu_nocache_npages;

	srmmu_nocache_npages =
		sysmemavail / SRMMU_NOCACHE_ALCRATIO / 1024 * 256;

 /* P3 XXX The 4x overuse: corroborated by /proc/meminfo. */
	// if (srmmu_nocache_npages < 256) srmmu_nocache_npages = 256;
	if (srmmu_nocache_npages < SRMMU_MIN_NOCACHE_PAGES)
		srmmu_nocache_npages = SRMMU_MIN_NOCACHE_PAGES;

	/* anything above 1280 blows up */
	if (srmmu_nocache_npages > SRMMU_MAX_NOCACHE_PAGES)
		srmmu_nocache_npages = SRMMU_MAX_NOCACHE_PAGES;

	srmmu_nocache_size = srmmu_nocache_npages * PAGE_SIZE;
	srmmu_nocache_end = SRMMU_NOCACHE_VADDR + srmmu_nocache_size;
}