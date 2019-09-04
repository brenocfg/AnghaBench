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
 char* get_charset_aliases () ; 
 char* getenv (char*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int strlen (char const*) ; 

const char *
locale_charset (void)
{
  const char *codeset;
  const char *aliases;

#if !(defined WINDOWS_NATIVE || defined OS2)

# if HAVE_LANGINFO_CODESET

  /* Most systems support nl_langinfo (CODESET) nowadays.  */
  codeset = nl_langinfo (CODESET);

#  ifdef __CYGWIN__
  /* Cygwin < 1.7 does not have locales.  nl_langinfo (CODESET) always
     returns "US-ASCII".  Return the suffix of the locale name from the
     environment variables (if present) or the codepage as a number.  */
  if (codeset != NULL && strcmp (codeset, "US-ASCII") == 0)
    {
      const char *locale;
      static char buf[2 + 10 + 1];

      locale = getenv ("LC_ALL");
      if (locale == NULL || locale[0] == '\0')
        {
          locale = getenv ("LC_CTYPE");
          if (locale == NULL || locale[0] == '\0')
            locale = getenv ("LANG");
        }
      if (locale != NULL && locale[0] != '\0')
        {
          /* If the locale name contains an encoding after the dot, return
             it.  */
          const char *dot = strchr (locale, '.');

          if (dot != NULL)
            {
              const char *modifier;

              dot++;
              /* Look for the possible @... trailer and remove it, if any.  */
              modifier = strchr (dot, '@');
              if (modifier == NULL)
                return dot;
              if (modifier - dot < sizeof (buf))
                {
                  memcpy (buf, dot, modifier - dot);
                  buf [modifier - dot] = '\0';
                  return buf;
                }
            }
        }

      /* The Windows API has a function returning the locale's codepage as a
         number: GetACP().  This encoding is used by Cygwin, unless the user
         has set the environment variable CYGWIN=codepage:oem (which very few
         people do).
         Output directed to console windows needs to be converted (to
         GetOEMCP() if the console is using a raster font, or to
         GetConsoleOutputCP() if it is using a TrueType font).  Cygwin does
         this conversion transparently (see winsup/cygwin/fhandler_console.cc),
         converting to GetConsoleOutputCP().  This leads to correct results,
         except when SetConsoleOutputCP has been called and a raster font is
         in use.  */
      sprintf (buf, "CP%u", GetACP ());
      codeset = buf;
    }
#  endif

# else

  /* On old systems which lack it, use setlocale or getenv.  */
  const char *locale = NULL;

  /* But most old systems don't have a complete set of locales.  Some
     (like SunOS 4 or DJGPP) have only the C locale.  Therefore we don't
     use setlocale here; it would return "C" when it doesn't support the
     locale name the user has set.  */
#  if 0
  locale = setlocale (LC_CTYPE, NULL);
#  endif
  if (locale == NULL || locale[0] == '\0')
    {
      locale = getenv ("LC_ALL");
      if (locale == NULL || locale[0] == '\0')
        {
          locale = getenv ("LC_CTYPE");
          if (locale == NULL || locale[0] == '\0')
            locale = getenv ("LANG");
        }
    }

  /* On some old systems, one used to set locale = "iso8859_1". On others,
     you set it to "language_COUNTRY.charset". In any case, we resolve it
     through the charset.alias file.  */
  codeset = locale;

# endif

#elif defined WINDOWS_NATIVE

  static char buf[2 + 10 + 1];

  /* The Windows API has a function returning the locale's codepage as
     a number, but the value doesn't change according to what the
     'setlocale' call specified.  So we use it as a last resort, in
     case the string returned by 'setlocale' doesn't specify the
     codepage.  */
  char *current_locale = setlocale (LC_ALL, NULL);
  char *pdot;

  /* If they set different locales for different categories,
     'setlocale' will return a semi-colon separated list of locale
     values.  To make sure we use the correct one, we choose LC_CTYPE.  */
  if (strchr (current_locale, ';'))
    current_locale = setlocale (LC_CTYPE, NULL);

  pdot = strrchr (current_locale, '.');
  if (pdot && 2 + strlen (pdot + 1) + 1 <= sizeof (buf))
    sprintf (buf, "CP%s", pdot + 1);
  else
    {
      /* The Windows API has a function returning the locale's codepage as a
        number: GetACP().
        When the output goes to a console window, it needs to be provided in
        GetOEMCP() encoding if the console is using a raster font, or in
        GetConsoleOutputCP() encoding if it is using a TrueType font.
        But in GUI programs and for output sent to files and pipes, GetACP()
        encoding is the best bet.  */
      sprintf (buf, "CP%u", GetACP ());
    }
  codeset = buf;

#elif defined OS2

  const char *locale;
  static char buf[2 + 10 + 1];
  ULONG cp[3];
  ULONG cplen;

  codeset = NULL;

  /* Allow user to override the codeset, as set in the operating system,
     with standard language environment variables.  */
  locale = getenv ("LC_ALL");
  if (locale == NULL || locale[0] == '\0')
    {
      locale = getenv ("LC_CTYPE");
      if (locale == NULL || locale[0] == '\0')
        locale = getenv ("LANG");
    }
  if (locale != NULL && locale[0] != '\0')
    {
      /* If the locale name contains an encoding after the dot, return it.  */
      const char *dot = strchr (locale, '.');

      if (dot != NULL)
        {
          const char *modifier;

          dot++;
          /* Look for the possible @... trailer and remove it, if any.  */
          modifier = strchr (dot, '@');
          if (modifier == NULL)
            return dot;
          if (modifier - dot < sizeof (buf))
            {
              memcpy (buf, dot, modifier - dot);
              buf [modifier - dot] = '\0';
              return buf;
            }
        }

      /* For the POSIX locale, don't use the system's codepage.  */
      if (strcmp (locale, "C") == 0 || strcmp (locale, "POSIX") == 0)
        codeset = "";
    }

  if (codeset == NULL)
    {
      /* OS/2 has a function returning the locale's codepage as a number.  */
      if (DosQueryCp (sizeof (cp), cp, &cplen))
        codeset = "";
      else
        {
          sprintf (buf, "CP%u", cp[0]);
          codeset = buf;
        }
    }

#endif

  if (codeset == NULL)
    /* The canonical name cannot be determined.  */
    codeset = "";

  /* Resolve alias. */
  for (aliases = get_charset_aliases ();
       *aliases != '\0';
       aliases += strlen (aliases) + 1, aliases += strlen (aliases) + 1)
    if (strcmp (codeset, aliases) == 0
        || (aliases[0] == '*' && aliases[1] == '\0'))
      {
        codeset = aliases + strlen (aliases) + 1;
        break;
      }

  /* Don't return an empty string.  GNU libc and GNU libiconv interpret
     the empty string as denoting "the locale's character encoding",
     thus GNU libiconv would call this function a second time.  */
  if (codeset[0] == '\0')
    codeset = "ASCII";

#ifdef DARWIN7
  /* Mac OS X sets MB_CUR_MAX to 1 when LC_ALL=C, and "UTF-8"
     (the default codeset) does not work when MB_CUR_MAX is 1.  */
  if (strcmp (codeset, "UTF-8") == 0 && MB_CUR_MAX_L (uselocale (NULL)) <= 1)
    codeset = "ASCII";
#endif

  return codeset;
}