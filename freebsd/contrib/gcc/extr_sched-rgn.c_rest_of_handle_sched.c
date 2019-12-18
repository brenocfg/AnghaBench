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
 int /*<<< orphan*/  schedule_insns () ; 

__attribute__((used)) static unsigned int
rest_of_handle_sched (void)
{
#ifdef INSN_SCHEDULING
  /* Do control and data sched analysis,
     and write some of the results to dump file.  */

  schedule_insns ();
#endif
  return 0;
}