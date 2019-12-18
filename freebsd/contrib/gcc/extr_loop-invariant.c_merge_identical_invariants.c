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
struct invariant {int dummy; } ;
typedef  int /*<<< orphan*/  htab_t ;

/* Variables and functions */
 scalar_t__ VEC_iterate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,struct invariant*) ; 
 int /*<<< orphan*/  VEC_length (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eq_invariant_expr ; 
 int /*<<< orphan*/  find_identical_invariants (int /*<<< orphan*/ ,struct invariant*) ; 
 int /*<<< orphan*/  free ; 
 int /*<<< orphan*/  hash_invariant_expr ; 
 int /*<<< orphan*/  htab_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htab_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invariant_p ; 
 int /*<<< orphan*/  invariants ; 

__attribute__((used)) static void
merge_identical_invariants (void)
{
  unsigned i;
  struct invariant *inv;
  htab_t eq = htab_create (VEC_length (invariant_p, invariants),
			   hash_invariant_expr, eq_invariant_expr, free);

  for (i = 0; VEC_iterate (invariant_p, invariants, i, inv); i++)
    find_identical_invariants (eq, inv);

  htab_delete (eq);
}