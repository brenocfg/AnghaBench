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

/* Variables and functions */
 int /*<<< orphan*/  flag_schedule_insns_after_reload ; 
 int optimize ; 

__attribute__((used)) static bool
gate_handle_split_before_regstack (void)
{
#if defined (HAVE_ATTR_length) && defined (STACK_REGS)
  /* If flow2 creates new instructions which need splitting
     and scheduling after reload is not done, they might not be
     split until final which doesn't allow splitting
     if HAVE_ATTR_length.  */
# ifdef INSN_SCHEDULING
  return (optimize && !flag_schedule_insns_after_reload);
# else
  return (optimize);
# endif
#else
  return 0;
#endif
}