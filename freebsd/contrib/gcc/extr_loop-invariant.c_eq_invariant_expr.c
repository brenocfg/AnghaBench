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
struct invariant_expr_entry {scalar_t__ mode; int /*<<< orphan*/  expr; TYPE_1__* inv; } ;
struct TYPE_2__ {int /*<<< orphan*/  insn; } ;

/* Variables and functions */
 int invariant_expr_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
eq_invariant_expr (const void *e1, const void *e2)
{
  const struct invariant_expr_entry *entry1 = e1;
  const struct invariant_expr_entry *entry2 = e2;

  if (entry1->mode != entry2->mode)
    return 0;

  return invariant_expr_equal_p (entry1->inv->insn, entry1->expr,
				 entry2->inv->insn, entry2->expr);
}