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
struct root_entry {int val; } ;
struct context_entry {int dummy; } ;

/* Variables and functions */
 int VTD_PAGE_MASK ; 
 int /*<<< orphan*/ * phys_to_virt (int) ; 
 scalar_t__ root_present (struct root_entry*) ; 

__attribute__((used)) static inline struct context_entry *
get_context_addr_from_root(struct root_entry *root)
{
	return (struct context_entry *)
		(root_present(root)?phys_to_virt(
		root->val & VTD_PAGE_MASK) :
		NULL);
}