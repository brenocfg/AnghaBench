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
typedef  int /*<<< orphan*/  ptid_t ;
typedef  enum target_signal { ____Placeholder_target_signal } target_signal ;

/* Variables and functions */
 int PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  printf_filtered (char*,int,int) ; 
 int resume_siggnal ; 
 int resume_step ; 
 scalar_t__ sr_get_debug () ; 

__attribute__((used)) static void
gdbsim_resume (ptid_t ptid, int step, enum target_signal siggnal)
{
  if (PIDGET (inferior_ptid) != 42)
    error ("The program is not being run.");

  if (sr_get_debug ())
    printf_filtered ("gdbsim_resume: step %d, signal %d\n", step, siggnal);

  resume_siggnal = siggnal;
  resume_step = step;
}