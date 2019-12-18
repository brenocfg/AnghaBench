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
struct root_entry {unsigned long val; } ;

/* Variables and functions */
 unsigned long VTD_PAGE_MASK ; 

__attribute__((used)) static inline void set_root_value(struct root_entry *root, unsigned long value)
{
	root->val |= value & VTD_PAGE_MASK;
}