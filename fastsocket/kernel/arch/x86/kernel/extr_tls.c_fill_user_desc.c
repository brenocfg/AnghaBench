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
struct user_desc {int entry_number; int contents; int read_exec_only; int seg_not_present; int /*<<< orphan*/  lm; int /*<<< orphan*/  useable; int /*<<< orphan*/  limit_in_pages; int /*<<< orphan*/  seg_32bit; int /*<<< orphan*/  limit; int /*<<< orphan*/  base_addr; } ;
struct desc_struct {int type; int /*<<< orphan*/  l; int /*<<< orphan*/  avl; int /*<<< orphan*/  p; int /*<<< orphan*/  g; int /*<<< orphan*/  d; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_desc_base (struct desc_struct const*) ; 
 int /*<<< orphan*/  get_desc_limit (struct desc_struct const*) ; 
 int /*<<< orphan*/  memset (struct user_desc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fill_user_desc(struct user_desc *info, int idx,
			   const struct desc_struct *desc)

{
	memset(info, 0, sizeof(*info));
	info->entry_number = idx;
	info->base_addr = get_desc_base(desc);
	info->limit = get_desc_limit(desc);
	info->seg_32bit = desc->d;
	info->contents = desc->type >> 2;
	info->read_exec_only = !(desc->type & 2);
	info->limit_in_pages = desc->g;
	info->seg_not_present = !desc->p;
	info->useable = desc->avl;
#ifdef CONFIG_X86_64
	info->lm = desc->l;
#endif
}