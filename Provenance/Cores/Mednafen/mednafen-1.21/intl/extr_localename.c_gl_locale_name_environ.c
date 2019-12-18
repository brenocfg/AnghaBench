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
 char* getenv (char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

const char *
gl_locale_name_environ (int category, const char *categoryname)
{
  const char *retval;

  /* Setting of LC_ALL overrides all other.  */
  retval = getenv ("LC_ALL");
  if (retval != NULL && retval[0] != '\0')
    return retval;
  /* Next comes the name of the desired category.  */
  retval = getenv (categoryname);
  if (retval != NULL && retval[0] != '\0')
    return retval;
  /* Last possibility is the LANG environment variable.  */
  retval = getenv ("LANG");
  if (retval != NULL && retval[0] != '\0')
    {
#if HAVE_CFLOCALECOPYCURRENT || HAVE_CFPREFERENCESCOPYAPPVALUE
      /* MacOS X 10.2 or newer.
         Ignore invalid LANG value set by the Terminal application.  */
      if (strcmp (retval, "UTF-8") != 0)
#endif
#if defined __CYGWIN__
      /* Cygwin.
         Ignore dummy LANG value set by ~/.profile.  */
      if (strcmp (retval, "C.UTF-8") != 0)
#endif
        return retval;
    }

  return NULL;
}