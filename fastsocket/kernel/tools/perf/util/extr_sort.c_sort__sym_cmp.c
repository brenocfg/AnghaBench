#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_6__ {TYPE_2__* sym; } ;
struct hist_entry {TYPE_1__ ms; scalar_t__ level; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_7__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 scalar_t__ _sort__sym_cmp (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cmp_null (TYPE_2__*,TYPE_2__*) ; 

__attribute__((used)) static int64_t
sort__sym_cmp(struct hist_entry *left, struct hist_entry *right)
{
	u64 ip_l, ip_r;

	if (!left->ms.sym && !right->ms.sym)
		return right->level - left->level;

	if (!left->ms.sym || !right->ms.sym)
		return cmp_null(left->ms.sym, right->ms.sym);

	if (left->ms.sym == right->ms.sym)
		return 0;

	ip_l = left->ms.sym->start;
	ip_r = right->ms.sym->start;

	return _sort__sym_cmp(left->ms.sym, right->ms.sym, ip_l, ip_r);
}