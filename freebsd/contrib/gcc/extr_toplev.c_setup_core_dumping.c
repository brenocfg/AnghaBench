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
struct rlimit {int /*<<< orphan*/  rlim_max; int /*<<< orphan*/  rlim_cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  RLIMIT_CORE ; 
 int /*<<< orphan*/  SIGABRT ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  diagnostic_abort_on_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal_error (char*) ; 
 scalar_t__ getrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  global_dc ; 
 scalar_t__ setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
setup_core_dumping (void)
{
#ifdef SIGABRT
  signal (SIGABRT, SIG_DFL);
#endif
#if defined(HAVE_SETRLIMIT)
  {
    struct rlimit rlim;
    if (getrlimit (RLIMIT_CORE, &rlim) != 0)
      fatal_error ("getting core file size maximum limit: %m");
    rlim.rlim_cur = rlim.rlim_max;
    if (setrlimit (RLIMIT_CORE, &rlim) != 0)
      fatal_error ("setting core file size limit to maximum: %m");
  }
#endif
  diagnostic_abort_on_error (global_dc);
}