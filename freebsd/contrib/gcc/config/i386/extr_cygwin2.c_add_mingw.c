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
 int /*<<< orphan*/  CYGWIN_MINGW_SUBDIR ; 
 scalar_t__ ISALNUM (char) ; 
 char** cvt_to_mingw ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memmove (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static void
add_mingw (void)
{
  char **av;
  char *p;
  for (av = cvt_to_mingw; *av; av++)
    {
      int sawcygwin = 0;
      while ((p = strstr (*av, "-cygwin")))
	{
	  char *over = p + sizeof ("-cygwin") - 1;
	  memmove (over + 1, over, strlen (over));
	  memcpy (p, "-mingw32", sizeof("-mingw32") - 1);
	  p = ++over;
	  while (ISALNUM (*p))
	    p++;
	  strcpy (over, p);
	  sawcygwin = 1;
	}
      if (!sawcygwin && !strstr (*av, "mingw"))
	strcat (*av, CYGWIN_MINGW_SUBDIR);
    }
}