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
 void* dir ; 
 int /*<<< orphan*/  error (char*) ; 
 void* machine ; 
 void* next (char**) ; 
 void* passwd ; 
 int /*<<< orphan*/  printf_unfiltered (char*,void*,void*,void*,void*) ; 
 void* user ; 

__attribute__((used)) static void
e7000_login_command (char *args, int from_tty)
{
  if (args)
    {
      machine = next (&args);
      user = next (&args);
      passwd = next (&args);
      dir = next (&args);
      if (from_tty)
	{
	  printf_unfiltered ("Set info to %s %s %s %s\n", machine, user, passwd, dir);
	}
    }
  else
    {
      error ("Syntax is ftplogin <machine> <user> <passwd> <directory>");
    }
}