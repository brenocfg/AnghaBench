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
typedef  int bfd_boolean ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strlen (char const*) ; 
 char* xmalloc (scalar_t__) ; 

__attribute__((used)) static const char *
realsymbol (const char *pattern)
{
  const char *p;
  bfd_boolean changed = FALSE, backslash = FALSE;
  char *s, *symbol = xmalloc (strlen (pattern) + 1);

  for (p = pattern, s = symbol; *p != '\0'; ++p)
    {
      /* It is a glob pattern only if there is no preceding
	 backslash.  */
      if (! backslash && (*p == '?' || *p == '*' || *p == '['))
	{
	  free (symbol);
	  return NULL;
	}

      if (backslash)
	{
	  /* Remove the preceding backslash.  */
	  *(s - 1) = *p;
	  changed = TRUE;
	}
      else
	*s++ = *p;

      backslash = *p == '\\';
    }

  if (changed)
    {
      *s = '\0';
      return symbol;
    }
  else
    {
      free (symbol);
      return pattern;
    }
}