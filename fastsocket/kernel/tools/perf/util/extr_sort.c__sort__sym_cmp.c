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
typedef  scalar_t__ u64 ;
struct symbol {scalar_t__ start; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  cmp_null (struct symbol*,struct symbol*) ; 

__attribute__((used)) static int64_t _sort__sym_cmp(struct symbol *sym_l, struct symbol *sym_r,
			      u64 ip_l, u64 ip_r)
{
	if (!sym_l || !sym_r)
		return cmp_null(sym_l, sym_r);

	if (sym_l == sym_r)
		return 0;

	if (sym_l)
		ip_l = sym_l->start;
	if (sym_r)
		ip_r = sym_r->start;

	return (int64_t)(ip_r - ip_l);
}