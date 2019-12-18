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
struct grant_entry {int dummy; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 struct grant_entry* __va (unsigned long) ; 

int arch_gnttab_map_shared(unsigned long *frames, unsigned long nr_gframes,
			   unsigned long max_nr_gframes,
			   struct grant_entry **__shared)
{
	*__shared = __va(frames[0] << PAGE_SHIFT);
	return 0;
}