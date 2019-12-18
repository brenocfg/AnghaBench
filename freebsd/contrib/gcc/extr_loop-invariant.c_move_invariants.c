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
struct loop {int dummy; } ;
struct invariant {int dummy; } ;

/* Variables and functions */
 scalar_t__ VEC_iterate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,struct invariant*) ; 
 int /*<<< orphan*/  invariant_p ; 
 int /*<<< orphan*/  invariants ; 
 int /*<<< orphan*/  move_invariant_reg (struct loop*,unsigned int) ; 

__attribute__((used)) static void
move_invariants (struct loop *loop)
{
  struct invariant *inv;
  unsigned i;

  for (i = 0; VEC_iterate (invariant_p, invariants, i, inv); i++)
    move_invariant_reg (loop, i);
}