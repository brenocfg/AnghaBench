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
 int /*<<< orphan*/  shell_escape (char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 char* xmalloc (int) ; 

__attribute__((used)) static void
make_command (char *arg, int from_tty)
{
  char *p;

  if (arg == 0)
    p = "make";
  else
    {
      p = xmalloc (sizeof ("make ") + strlen (arg));
      strcpy (p, "make ");
      strcpy (p + sizeof ("make ") - 1, arg);
    }

  shell_escape (p, from_tty);
}