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
 int /*<<< orphan*/  maintenance_do_deprecate (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_unfiltered (char*) ; 

__attribute__((used)) static void
maintenance_undeprecate (char *args, int from_tty)
{
  if (args == NULL || *args == '\0')
    {
      printf_unfiltered ("\"maintenance undeprecate\" takes an argument, \n\
the command you want to undeprecate.\n");
    }

  maintenance_do_deprecate (args, 0);

}