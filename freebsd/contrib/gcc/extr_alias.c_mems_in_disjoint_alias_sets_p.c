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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_ALIAS_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alias_sets_conflict_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ flag_strict_aliasing ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

__attribute__((used)) static inline int
mems_in_disjoint_alias_sets_p (rtx mem1, rtx mem2)
{
/* Perform a basic sanity check.  Namely, that there are no alias sets
   if we're not using strict aliasing.  This helps to catch bugs
   whereby someone uses PUT_CODE, but doesn't clear MEM_ALIAS_SET, or
   where a MEM is allocated in some way other than by the use of
   gen_rtx_MEM, and the MEM_ALIAS_SET is not cleared.  If we begin to
   use alias sets to indicate that spilled registers cannot alias each
   other, we might need to remove this check.  */
  gcc_assert (flag_strict_aliasing
	      || (!MEM_ALIAS_SET (mem1) && !MEM_ALIAS_SET (mem2)));

  return ! alias_sets_conflict_p (MEM_ALIAS_SET (mem1), MEM_ALIAS_SET (mem2));
}