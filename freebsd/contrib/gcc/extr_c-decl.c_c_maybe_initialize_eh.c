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
 scalar_t__ USING_SJLJ_EXCEPTIONS ; 
 int c_eh_initialized_p ; 
 int /*<<< orphan*/  default_init_unwind_resume_libfunc () ; 
 int /*<<< orphan*/  eh_personality_libfunc ; 
 int /*<<< orphan*/  flag_exceptions ; 
 int /*<<< orphan*/  init_one_libfunc (char*) ; 
 int /*<<< orphan*/  using_eh_for_cleanups () ; 

void
c_maybe_initialize_eh (void)
{
  if (!flag_exceptions || c_eh_initialized_p)
    return;

  c_eh_initialized_p = true;
  eh_personality_libfunc
    = init_one_libfunc (USING_SJLJ_EXCEPTIONS
			? "__gcc_personality_sj0"
			: "__gcc_personality_v0");
  default_init_unwind_resume_libfunc ();
  using_eh_for_cleanups ();
}