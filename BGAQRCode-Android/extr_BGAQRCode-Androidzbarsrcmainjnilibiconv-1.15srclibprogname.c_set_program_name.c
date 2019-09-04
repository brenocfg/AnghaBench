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
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 char const* program_name ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 char* strrchr (char const*,char) ; 

void
set_program_name (const char *argv0)
{
  /* libtool creates a temporary executable whose name is sometimes prefixed
     with "lt-" (depends on the platform).  It also makes argv[0] absolute.
     But the name of the temporary executable is a detail that should not be
     visible to the end user and to the test suite.
     Remove this "<dirname>/.libs/" or "<dirname>/.libs/lt-" prefix here.  */
  const char *slash;
  const char *base;

  /* Sanity check.  POSIX requires the invoking process to pass a non-NULL
     argv[0].  */
  if (argv0 == NULL)
    {
      /* It's a bug in the invoking program.  Help diagnosing it.  */
      fputs ("A NULL argv[0] was passed through an exec system call.\n",
             stderr);
      abort ();
    }

  slash = strrchr (argv0, '/');
  base = (slash != NULL ? slash + 1 : argv0);
  if (base - argv0 >= 7 && strncmp (base - 7, "/.libs/", 7) == 0)
    {
      argv0 = base;
      if (strncmp (base, "lt-", 3) == 0)
        {
          argv0 = base + 3;
          /* On glibc systems, remove the "lt-" prefix from the variable
             program_invocation_short_name.  */
#if HAVE_DECL_PROGRAM_INVOCATION_SHORT_NAME
          program_invocation_short_name = (char *) argv0;
#endif
        }
    }

  /* But don't strip off a leading <dirname>/ in general, because when the user
     runs
         /some/hidden/place/bin/cp foo foo
     he should get the error message
         /some/hidden/place/bin/cp: `foo' and `foo' are the same file
     not
         cp: `foo' and `foo' are the same file
   */

  program_name = argv0;

  /* On glibc systems, the error() function comes from libc and uses the
     variable program_invocation_name, not program_name.  So set this variable
     as well.  */
#if HAVE_DECL_PROGRAM_INVOCATION_NAME
  program_invocation_name = (char *) argv0;
#endif
}