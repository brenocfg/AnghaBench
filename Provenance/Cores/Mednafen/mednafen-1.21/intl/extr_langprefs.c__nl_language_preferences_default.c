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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/ * HMODULE ;
typedef  int /*<<< orphan*/ * CFTypeRef ;
typedef  int /*<<< orphan*/  CFStringRef ;
typedef  int /*<<< orphan*/  CFArrayRef ;

/* Variables and functions */
 int CFArrayGetCount (int /*<<< orphan*/ ) ; 
 scalar_t__ CFArrayGetTypeID () ; 
 int /*<<< orphan*/ * CFArrayGetValueAtIndex (int /*<<< orphan*/ ,int) ; 
 scalar_t__ CFGetTypeID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CFPreferencesCopyAppValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFSTR (char*) ; 
 scalar_t__ CFStringGetCString (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ CFStringGetTypeID () ; 
 int /*<<< orphan*/ * GetModuleHandle (char*) ; 
 char* _nl_language_preferences_win32_95 () ; 
 char* _nl_language_preferences_win32_ME (int /*<<< orphan*/ *) ; 
 char* _nl_language_preferences_win32_mui (int /*<<< orphan*/ *) ; 
 char* _nl_language_preferences_win32_system (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _nl_locale_name_canonicalize (char*) ; 
 int /*<<< orphan*/ * getenv (char*) ; 
 int /*<<< orphan*/  kCFPreferencesCurrentApplication ; 
 int /*<<< orphan*/  kCFStringEncodingASCII ; 
 scalar_t__ malloc (size_t) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

const char *
_nl_language_preferences_default (void)
{
#if HAVE_CFPREFERENCESCOPYAPPVALUE /* MacOS X 10.2 or newer */
  {
    /* Cache the preferences list, since CoreFoundation calls are expensive.  */
    static const char *cached_languages;
    static int cache_initialized;

    if (!cache_initialized)
      {
        CFTypeRef preferences =
          CFPreferencesCopyAppValue (CFSTR ("AppleLanguages"),
                                     kCFPreferencesCurrentApplication);
        if (preferences != NULL
            && CFGetTypeID (preferences) == CFArrayGetTypeID ())
          {
            CFArrayRef prefArray = (CFArrayRef)preferences;
            int n = CFArrayGetCount (prefArray);
            char buf[256];
            size_t size = 0;
            int i;

            for (i = 0; i < n; i++)
              {
                CFTypeRef element = CFArrayGetValueAtIndex (prefArray, i);
                if (element != NULL
                    && CFGetTypeID (element) == CFStringGetTypeID ()
                    && CFStringGetCString ((CFStringRef)element,
                                           buf, sizeof (buf),
                                           kCFStringEncodingASCII))
                  {
                    _nl_locale_name_canonicalize (buf);
                    size += strlen (buf) + 1;
                    /* Most GNU programs use msgids in English and don't ship
                       an en.mo message catalog.  Therefore when we see "en"
                       in the preferences list, arrange for gettext() to
                       return the msgid, and ignore all further elements of
                       the preferences list.  */
                    if (strcmp (buf, "en") == 0)
                      break;
                  }
                else
                  break;
              }
            if (size > 0)
              {
                char *languages = (char *) malloc (size);

                if (languages != NULL)
                  {
                    char *p = languages;

                    for (i = 0; i < n; i++)
                      {
                        CFTypeRef element =
                          CFArrayGetValueAtIndex (prefArray, i);
                        if (element != NULL
                            && CFGetTypeID (element) == CFStringGetTypeID ()
                            && CFStringGetCString ((CFStringRef)element,
                                                   buf, sizeof (buf),
                                                   kCFStringEncodingASCII))
                          {
                            _nl_locale_name_canonicalize (buf);
                            strcpy (p, buf);
                            p += strlen (buf);
                            *p++ = ':';
                            if (strcmp (buf, "en") == 0)
                              break;
                          }
                        else
                          break;
                      }
                    *--p = '\0';

                    cached_languages = languages;
                  }
              }
          }
        cache_initialized = 1;
      }
    if (cached_languages != NULL)
      return cached_languages;
  }
#endif

#ifdef WIN32_NATIVE
  {
    /* Cache the preferences list, since computing it is expensive.  */
    static const char *cached_languages;
    static int cache_initialized;

    /* Activate the new code only when the GETTEXT_MUI environment variable is
       set, for the time being, since the new code is not well tested.  */
    if (!cache_initialized && getenv ("GETTEXT_MUI") != NULL)
      {
        const char *languages = NULL;
        HMODULE kernel32 = GetModuleHandle ("kernel32");

        if (kernel32 != NULL)
          languages = _nl_language_preferences_win32_mui (kernel32);

        if (languages == NULL && kernel32 != NULL)
          languages = _nl_language_preferences_win32_ME (kernel32);

        if (languages == NULL)
          languages = _nl_language_preferences_win32_95 ();

        if (languages == NULL && kernel32 != NULL)
          languages = _nl_language_preferences_win32_system (kernel32);

        cached_languages = languages;
        cache_initialized = 1;
      }
    if (cached_languages != NULL)
      return cached_languages;
  }
#endif

  return NULL;
}