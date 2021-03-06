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
 int /*<<< orphan*/  printf_unfiltered (char*) ; 
 int strtol (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
maintenance_time_display (char *args, int from_tty)
{
  extern int display_time;

  if (args == NULL || *args == '\0')
    printf_unfiltered ("\"maintenance time\" takes a numeric argument.\n");
  else
    display_time = strtol (args, NULL, 10);
}