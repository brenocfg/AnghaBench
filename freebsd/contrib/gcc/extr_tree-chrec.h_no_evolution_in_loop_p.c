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
typedef  scalar_t__ tree ;

/* Variables and functions */
 scalar_t__ chrec_contains_symbols_defined_in_loop (scalar_t__,unsigned int) ; 
 scalar_t__ chrec_dont_know ; 
 scalar_t__ chrec_not_analyzed_yet ; 
 scalar_t__ hide_evolution_in_other_loops_than_loop (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  tree_is_chrec (scalar_t__) ; 

__attribute__((used)) static inline bool
no_evolution_in_loop_p (tree chrec, unsigned loop_num, bool *res)
{
  tree scev;
  
  if (chrec == chrec_not_analyzed_yet
      || chrec == chrec_dont_know
      || chrec_contains_symbols_defined_in_loop (chrec, loop_num))
    return false;

  scev = hide_evolution_in_other_loops_than_loop (chrec, loop_num);
  *res = !tree_is_chrec (scev);
  return true;
}