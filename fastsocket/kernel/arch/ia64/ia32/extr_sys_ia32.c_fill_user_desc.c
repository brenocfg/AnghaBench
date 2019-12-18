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
struct ia32_user_desc {int entry_number; int read_exec_only; int seg_not_present; int /*<<< orphan*/  useable; int /*<<< orphan*/  limit_in_pages; int /*<<< orphan*/  contents; int /*<<< orphan*/  seg_32bit; int /*<<< orphan*/  limit; int /*<<< orphan*/  base_addr; } ;
struct desc_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_32BIT (struct desc_struct const*) ; 
 int /*<<< orphan*/  GET_BASE (struct desc_struct const*) ; 
 int /*<<< orphan*/  GET_CONTENTS (struct desc_struct const*) ; 
 int /*<<< orphan*/  GET_LIMIT (struct desc_struct const*) ; 
 int /*<<< orphan*/  GET_LIMIT_PAGES (struct desc_struct const*) ; 
 int /*<<< orphan*/  GET_PRESENT (struct desc_struct const*) ; 
 int /*<<< orphan*/  GET_USEABLE (struct desc_struct const*) ; 
 int /*<<< orphan*/  GET_WRITABLE (struct desc_struct const*) ; 

__attribute__((used)) static void fill_user_desc(struct ia32_user_desc *info, int idx,
		const struct desc_struct *desc)
{
	info->entry_number = idx;
	info->base_addr = GET_BASE(desc);
	info->limit = GET_LIMIT(desc);
	info->seg_32bit = GET_32BIT(desc);
	info->contents = GET_CONTENTS(desc);
	info->read_exec_only = !GET_WRITABLE(desc);
	info->limit_in_pages = GET_LIMIT_PAGES(desc);
	info->seg_not_present = !GET_PRESENT(desc);
	info->useable = GET_USEABLE(desc);
}