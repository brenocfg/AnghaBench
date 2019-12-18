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
 int DMGL_ANSI ; 
 int DMGL_PARAMS ; 
 int /*<<< orphan*/  current_language ; 
 char* language_demangle (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  printf_unfiltered (char*,...) ; 
 int /*<<< orphan*/  xfree (char*) ; 

__attribute__((used)) static void
maintenance_demangle (char *args, int from_tty)
{
  char *demangled;

  if (args == NULL || *args == '\0')
    {
      printf_unfiltered ("\"maintenance demangle\" takes an argument to demangle.\n");
    }
  else
    {
      demangled = language_demangle (current_language, args, 
				     DMGL_ANSI | DMGL_PARAMS);
      if (demangled != NULL)
	{
	  printf_unfiltered ("%s\n", demangled);
	  xfree (demangled);
	}
      else
	{
	  printf_unfiltered ("Can't demangle \"%s\"\n", args);
	}
    }
}