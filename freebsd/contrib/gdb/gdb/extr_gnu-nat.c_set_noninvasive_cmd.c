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
 scalar_t__ parse_bool_arg (char*,char*) ; 
 int /*<<< orphan*/  set_exceptions_cmd (char*,int) ; 
 int /*<<< orphan*/  set_signals_cmd (char*,int) ; 
 int /*<<< orphan*/  set_task_pause_cmd (char*,int) ; 

__attribute__((used)) static void
set_noninvasive_cmd (char *args, int from_tty)
{
  /* Invert the sense of the arg for each component.  */
  char *inv_args = parse_bool_arg (args, "set noninvasive") ? "off" : "on";

  set_task_pause_cmd (inv_args, from_tty);
  set_signals_cmd (inv_args, from_tty);
  set_exceptions_cmd (inv_args, from_tty);
}