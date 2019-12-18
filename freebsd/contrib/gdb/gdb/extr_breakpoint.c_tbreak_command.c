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
 int /*<<< orphan*/  BP_TEMPFLAG ; 
 int /*<<< orphan*/  break_command_1 (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

void
tbreak_command (char *arg, int from_tty)
{
  break_command_1 (arg, BP_TEMPFLAG, from_tty, NULL);
}