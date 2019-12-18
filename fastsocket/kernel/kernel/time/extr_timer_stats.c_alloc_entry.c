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
struct entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ MAX_ENTRIES ; 
 struct entry* entries ; 
 scalar_t__ nr_entries ; 

__attribute__((used)) static struct entry *alloc_entry(void)
{
	if (nr_entries >= MAX_ENTRIES)
		return NULL;

	return entries + nr_entries++;
}