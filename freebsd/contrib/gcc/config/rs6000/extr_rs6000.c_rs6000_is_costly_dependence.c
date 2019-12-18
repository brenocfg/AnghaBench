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
 scalar_t__ REG_NOTE_KIND (int /*<<< orphan*/ ) ; 
 scalar_t__ all_deps_costly ; 
 scalar_t__ is_load_insn (int /*<<< orphan*/ ) ; 
 scalar_t__ is_store_insn (int /*<<< orphan*/ ) ; 
 scalar_t__ max_dep_latency ; 
 scalar_t__ no_dep_costly ; 
 scalar_t__ rs6000_sched_costly_dep ; 
 scalar_t__ store_to_load_dep_costly ; 
 scalar_t__ true_store_to_load_dep_costly ; 

__attribute__((used)) static bool
rs6000_is_costly_dependence (rtx insn, rtx next, rtx link, int cost,
			     int distance)
{
  /* If the flag is not enabled - no dependence is considered costly;
     allow all dependent insns in the same group.
     This is the most aggressive option.  */
  if (rs6000_sched_costly_dep == no_dep_costly)
    return false;

  /* If the flag is set to 1 - a dependence is always considered costly;
     do not allow dependent instructions in the same group.
     This is the most conservative option.  */
  if (rs6000_sched_costly_dep == all_deps_costly)
    return true;

  if (rs6000_sched_costly_dep == store_to_load_dep_costly
      && is_load_insn (next)
      && is_store_insn (insn))
    /* Prevent load after store in the same group.  */
    return true;

  if (rs6000_sched_costly_dep == true_store_to_load_dep_costly
      && is_load_insn (next)
      && is_store_insn (insn)
      && (!link || (int) REG_NOTE_KIND (link) == 0))
     /* Prevent load after store in the same group if it is a true
	dependence.  */
     return true;

  /* The flag is set to X; dependences with latency >= X are considered costly,
     and will not be scheduled in the same group.  */
  if (rs6000_sched_costly_dep <= max_dep_latency
      && ((cost - distance) >= (int)rs6000_sched_costly_dep))
    return true;

  return false;
}