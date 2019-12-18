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
struct type {int dummy; } ;
struct agent_expr {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_agent_expr (struct agent_expr*) ; 
 int /*<<< orphan*/  gen_conversion (struct agent_expr*,struct type*,struct type*) ; 
 struct agent_expr* new_agent_expr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
is_nontrivial_conversion (struct type *from, struct type *to)
{
  struct agent_expr *ax = new_agent_expr (0);
  int nontrivial;

  /* Actually generate the code, and see if anything came out.  At the
     moment, it would be trivial to replicate the code in
     gen_conversion here, but in the future, when we're supporting
     floating point and the like, it may not be.  Doing things this
     way allows this function to be independent of the logic in
     gen_conversion.  */
  gen_conversion (ax, from, to);
  nontrivial = ax->len > 0;
  free_agent_expr (ax);
  return nontrivial;
}