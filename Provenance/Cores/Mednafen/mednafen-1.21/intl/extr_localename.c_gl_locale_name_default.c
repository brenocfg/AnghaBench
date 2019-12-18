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
typedef  int /*<<< orphan*/  namebuf ;
typedef  int /*<<< orphan*/  LCID ;
typedef  int /*<<< orphan*/ * CFTypeRef ;
typedef  int /*<<< orphan*/  CFStringRef ;
typedef  int /*<<< orphan*/  CFLocaleRef ;

/* Variables and functions */
 scalar_t__ CFGetTypeID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CFLocaleCopyCurrent () ; 
 int /*<<< orphan*/  CFLocaleGetIdentifier (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CFPreferencesCopyAppValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFSTR (char*) ; 
 scalar_t__ CFStringGetCString (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ CFStringGetTypeID () ; 
 int /*<<< orphan*/  GetThreadLocale () ; 
 int /*<<< orphan*/  gl_locale_name_canonicalize (char*) ; 
 char const* gl_locale_name_from_win32_LCID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kCFPreferencesCurrentApplication ; 
 int /*<<< orphan*/  kCFStringEncodingASCII ; 
 char* strdup (char*) ; 

const char *
gl_locale_name_default (void)
{
  /* POSIX:2001 says:
     "All implementations shall define a locale as the default locale, to be
      invoked when no environment variables are set, or set to the empty
      string.  This default locale can be the POSIX locale or any other
      implementation-defined locale.  Some implementations may provide
      facilities for local installation administrators to set the default
      locale, customizing it for each location.  POSIX:2001 does not require
      such a facility.

     The systems with such a facility are MacOS X and Windows: They provide a
     GUI that allows the user to choose a locale.
       - On MacOS X, by default, none of LC_* or LANG are set.  Starting with
         MacOS X 10.4 or 10.5, LANG is set for processes launched by the
         'Terminal' application (but sometimes to an incorrect value "UTF-8").
         When no environment variable is set, setlocale (LC_ALL, "") uses the
         "C" locale.
       - On native Windows, by default, none of LC_* or LANG are set.
         When no environment variable is set, setlocale (LC_ALL, "") uses the
         locale chosen by the user.
       - On Cygwin 1.5.x, by default, none of LC_* or LANG are set.
         When no environment variable is set, setlocale (LC_ALL, "") uses the
         "C" locale.
       - On Cygwin 1.7, by default, LANG is set to "C.UTF-8" when the default
         ~/.profile is executed.
         When no environment variable is set, setlocale (LC_ALL, "") uses the
         "C.UTF-8" locale, which operates in the same way as the "C" locale.
  */

#if !(HAVE_CFLOCALECOPYCURRENT || HAVE_CFPREFERENCESCOPYAPPVALUE || defined WIN32_NATIVE || defined __CYGWIN__)

  /* The system does not have a way of setting the locale, other than the
     POSIX specified environment variables.  We use C as default locale.  */
  return "C";

#else

  /* Return an XPG style locale name language[_territory][@modifier].
     Don't even bother determining the codeset; it's not useful in this
     context, because message catalogs are not specific to a single
     codeset.  */

# if HAVE_CFLOCALECOPYCURRENT || HAVE_CFPREFERENCESCOPYAPPVALUE
  /* MacOS X 10.2 or newer */
  {
    /* Cache the locale name, since CoreFoundation calls are expensive.  */
    static const char *cached_localename;

    if (cached_localename == NULL)
      {
        char namebuf[256];
#  if HAVE_CFLOCALECOPYCURRENT /* MacOS X 10.3 or newer */
        CFLocaleRef locale = CFLocaleCopyCurrent ();
        CFStringRef name = CFLocaleGetIdentifier (locale);

        if (CFStringGetCString (name, namebuf, sizeof (namebuf),
                                kCFStringEncodingASCII))
          {
            gl_locale_name_canonicalize (namebuf);
            cached_localename = strdup (namebuf);
          }
        CFRelease (locale);
#  elif HAVE_CFPREFERENCESCOPYAPPVALUE /* MacOS X 10.2 or newer */
        CFTypeRef value =
          CFPreferencesCopyAppValue (CFSTR ("AppleLocale"),
                                     kCFPreferencesCurrentApplication);
        if (value != NULL
            && CFGetTypeID (value) == CFStringGetTypeID ()
            && CFStringGetCString ((CFStringRef)value,
                                   namebuf, sizeof (namebuf),
                                   kCFStringEncodingASCII))
          {
            gl_locale_name_canonicalize (namebuf);
            cached_localename = strdup (namebuf);
          }
#  endif
        if (cached_localename == NULL)
          cached_localename = "C";
      }
    return cached_localename;
  }

# endif

# if defined WIN32_NATIVE || defined __CYGWIN__ /* WIN32 or Cygwin */
  {
    LCID lcid;

    /* Use native Win32 API locale ID.  */
    lcid = GetThreadLocale ();

    return gl_locale_name_from_win32_LCID (lcid);
  }
# endif
#endif
}