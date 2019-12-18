#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* spec_info_t ;
struct TYPE_5__ {unsigned int flags; } ;
struct TYPE_4__ {int mask; int /*<<< orphan*/  flags; scalar_t__ dump; } ;

/* Variables and functions */
 int BEGIN_CONTROL ; 
 int BEGIN_DATA ; 
 int BE_IN_CONTROL ; 
 int BE_IN_DATA ; 
 int CONTROL_SPEC ; 
 int /*<<< orphan*/  COUNT_SPEC_IN_CRITICAL_PATH ; 
 int DATA_SPEC ; 
 unsigned int DETACH_LIFE_INFO ; 
 unsigned int DO_SPECULATION ; 
 int /*<<< orphan*/  PREFER_NON_CONTROL_SPEC ; 
 int /*<<< orphan*/  PREFER_NON_DATA_SPEC ; 
 unsigned int SCHED_EBB ; 
 unsigned int SCHED_RGN ; 
 unsigned int USE_DEPS_LIST ; 
 unsigned int USE_GLAT ; 
 TYPE_3__* current_sched_info ; 
 int /*<<< orphan*/  gcc_assert (unsigned int) ; 
 scalar_t__ mflag_sched_ar_data_spec ; 
 scalar_t__ mflag_sched_ar_in_data_spec ; 
 scalar_t__ mflag_sched_br_data_spec ; 
 scalar_t__ mflag_sched_br_in_data_spec ; 
 scalar_t__ mflag_sched_control_spec ; 
 scalar_t__ mflag_sched_count_spec_in_critical_path ; 
 scalar_t__ mflag_sched_in_control_spec ; 
 scalar_t__ mflag_sched_prefer_non_control_spec_insns ; 
 scalar_t__ mflag_sched_prefer_non_data_spec_insns ; 
 scalar_t__ mflag_sched_spec_verbose ; 
 scalar_t__ optimize ; 
 scalar_t__ reload_completed ; 
 scalar_t__ sched_dump ; 
 int sched_verbose ; 
 scalar_t__ stderr ; 

__attribute__((used)) static void
ia64_set_sched_flags (spec_info_t spec_info)
{
  unsigned int *flags = &(current_sched_info->flags);

  if (*flags & SCHED_RGN
      || *flags & SCHED_EBB)  
    {
      int mask = 0;

      if ((mflag_sched_br_data_spec && !reload_completed && optimize > 0)
	  || (mflag_sched_ar_data_spec && reload_completed))
	{
	  mask |= BEGIN_DATA;
	  
	  if ((mflag_sched_br_in_data_spec && !reload_completed)
	      || (mflag_sched_ar_in_data_spec && reload_completed))
	    mask |= BE_IN_DATA;
	}
      
      if (mflag_sched_control_spec)
	{
	  mask |= BEGIN_CONTROL;
	  
	  if (mflag_sched_in_control_spec)
	    mask |= BE_IN_CONTROL;
	}

      gcc_assert (*flags & USE_GLAT);

      if (mask)
	{
	  *flags |= USE_DEPS_LIST | DETACH_LIFE_INFO | DO_SPECULATION;
	  
	  spec_info->mask = mask;
	  spec_info->flags = 0;
      
	  if ((mask & DATA_SPEC) && mflag_sched_prefer_non_data_spec_insns)
	    spec_info->flags |= PREFER_NON_DATA_SPEC;

	  if ((mask & CONTROL_SPEC)
	      && mflag_sched_prefer_non_control_spec_insns)
	    spec_info->flags |= PREFER_NON_CONTROL_SPEC;

	  if (mflag_sched_spec_verbose)
	    {
	      if (sched_verbose >= 1)
		spec_info->dump = sched_dump;
	      else
		spec_info->dump = stderr;
	    }
	  else
	    spec_info->dump = 0;
	  
	  if (mflag_sched_count_spec_in_critical_path)
	    spec_info->flags |= COUNT_SPEC_IN_CRITICAL_PATH;
	}
    }
}