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
 int /*<<< orphan*/  getpid () ; 
 int kill (int /*<<< orphan*/ ,int) ; 

int
rpl_raise (int sig)
{
#if GNULIB_defined_signal_blocking && GNULIB_defined_SIGPIPE
  if (sig == SIGPIPE)
    return _gl_raise_SIGPIPE ();
#endif

#if HAVE_RAISE
  return raise_nothrow (sig);
#else
  return kill (getpid (), sig);
#endif
}