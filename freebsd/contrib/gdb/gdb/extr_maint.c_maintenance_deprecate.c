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
 int /*<<< orphan*/  maintenance_do_deprecate (char*,int) ; 
 int /*<<< orphan*/  printf_unfiltered (char*) ; 

__attribute__((used)) static void
maintenance_deprecate (char *args, int from_tty)
{
  if (args == NULL || *args == '\0')
    {
      printf_unfiltered ("\"maintenance deprecate\" takes an argument, \n\
the command you want to deprecate, and optionally the replacement command \n\
enclosed in quotes.\n");
    }

  maintenance_do_deprecate (args, 1);

}