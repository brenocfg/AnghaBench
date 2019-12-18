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
struct ui_out {int dummy; } ;
struct captured_execute_command_args {int /*<<< orphan*/  from_tty; int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int GDB_RC_OK ; 
 int /*<<< orphan*/  execute_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
do_captured_execute_command (struct ui_out *uiout, void *data)
{
  struct captured_execute_command_args *args =
    (struct captured_execute_command_args *) data;
  execute_command (args->command, args->from_tty);
  return GDB_RC_OK;
}