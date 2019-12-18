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
 char const* gl_locale_name_environ (int,char const*) ; 
 char const* setlocale (int,int /*<<< orphan*/ *) ; 

const char *
gl_locale_name_posix (int category, const char *categoryname)
{
  /* Use the POSIX methods of looking to 'LC_ALL', 'LC_xxx', and 'LANG'.
     On some systems this can be done by the 'setlocale' function itself.  */
#if defined HAVE_SETLOCALE && defined HAVE_LC_MESSAGES && defined HAVE_LOCALE_NULL
  return setlocale (category, NULL);
#else
  /* On other systems we ignore what setlocale reports and instead look at the
     environment variables directly.  This is necessary
       1. on systems which have a facility for customizing the default locale
          (MacOS X, native Windows, Cygwin) and where the system's setlocale()
          function ignores this default locale (MacOS X, Cygwin), in two cases:
          a. when the user missed to use the setlocale() override from libintl
             (for example by not including <libintl.h>),
          b. when setlocale supports only the "C" locale, such as on Cygwin
             1.5.x.  In this case even the override from libintl cannot help.
       2. on all systems where setlocale supports only the "C" locale.  */
  /* Strictly speaking, it is a POSIX violation to look at the environment
     variables regardless whether setlocale has been called or not.  POSIX
     says:
         "For C-language programs, the POSIX locale shall be the
          default locale when the setlocale() function is not called."
     But we assume that all programs that use internationalized APIs call
     setlocale (LC_ALL, "").  */
  return gl_locale_name_environ (category, categoryname);
#endif
}