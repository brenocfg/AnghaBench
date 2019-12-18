#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hist_entry {scalar_t__ level; TYPE_1__* branch_info; } ;
struct addr_map_symbol {int /*<<< orphan*/  addr; int /*<<< orphan*/  sym; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_2__ {struct addr_map_symbol from; } ;

/* Variables and functions */
 scalar_t__ _sort__sym_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64_t
sort__sym_from_cmp(struct hist_entry *left, struct hist_entry *right)
{
	struct addr_map_symbol *from_l = &left->branch_info->from;
	struct addr_map_symbol *from_r = &right->branch_info->from;

	if (!from_l->sym && !from_r->sym)
		return right->level - left->level;

	return _sort__sym_cmp(from_l->sym, from_r->sym, from_l->addr,
			     from_r->addr);
}