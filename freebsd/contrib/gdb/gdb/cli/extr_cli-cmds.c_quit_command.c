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
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  quit_confirm () ; 
 int /*<<< orphan*/  quit_force (char*,int) ; 

void
quit_command (char *args, int from_tty)
{
  if (!quit_confirm ())
    error ("Not confirmed.");
  quit_force (args, from_tty);
}