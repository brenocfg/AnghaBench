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
struct alloc_info {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRY_IN_USE ; 
 struct alloc_info* simple_find_entry (void*) ; 

__attribute__((used)) static void simple_free(void *ptr)
{
	struct alloc_info *p = simple_find_entry(ptr);

	if (p != NULL)
		p->flags &= ~ENTRY_IN_USE;
}