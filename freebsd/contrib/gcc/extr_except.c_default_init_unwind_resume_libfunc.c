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
 int /*<<< orphan*/  init_one_libfunc (char*) ; 
 int /*<<< orphan*/  unwind_resume_libfunc ; 

void
default_init_unwind_resume_libfunc (void)
{
  /* The default c++ routines aren't actually c++ specific, so use those.  */
  unwind_resume_libfunc =
    init_one_libfunc ( USING_SJLJ_EXCEPTIONS ? "_Unwind_SjLj_Resume"
					     : "_Unwind_Resume");
}