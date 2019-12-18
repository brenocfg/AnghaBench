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
 int /*<<< orphan*/  current_gdbarch ; 
 char* gdbarch_construct_inferior_arguments (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ inferior_argc ; 
 char* inferior_args ; 
 int /*<<< orphan*/  inferior_argv ; 
 char* set_inferior_args (char*) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 char* xstrdup (char*) ; 

char *
get_inferior_args (void)
{
  if (inferior_argc != 0)
    {
      char *n, *old;

      n = gdbarch_construct_inferior_arguments (current_gdbarch,
						inferior_argc, inferior_argv);
      old = set_inferior_args (n);
      xfree (old);
    }

  if (inferior_args == NULL)
    inferior_args = xstrdup ("");

  return inferior_args;
}