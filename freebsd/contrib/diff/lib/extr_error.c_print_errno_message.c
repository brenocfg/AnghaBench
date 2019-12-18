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
 char* _ (char*) ; 
 scalar_t__ _IO_fwide (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __fwprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 char* __strerror_r (int,char*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 

__attribute__((used)) static void
print_errno_message (int errnum)
{
  char const *s;

#if defined HAVE_STRERROR_R || _LIBC
  char errbuf[1024];
# if STRERROR_R_CHAR_P || _LIBC
  s = __strerror_r (errnum, errbuf, sizeof errbuf);
# else
  if (__strerror_r (errnum, errbuf, sizeof errbuf) == 0)
    s = errbuf;
  else
    s = 0;
# endif
#else
  s = strerror (errnum);
#endif

#if !_LIBC
  if (! s)
    s = _("Unknown system error");
#endif

#if _LIBC
  if (_IO_fwide (stderr, 0) > 0)
    {
      __fwprintf (stderr, L": %s", s);
      return;
    }
#endif

  fprintf (stderr, ": %s", s);
}