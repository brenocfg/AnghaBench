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
struct command_line {int dummy; } ;
struct cleanup {int dummy; } ;
typedef  enum command_control_type { ____Placeholder_command_control_type } command_control_type ;

/* Variables and functions */
 struct command_line* build_command_line (int,char*) ; 
 int /*<<< orphan*/  discard_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 scalar_t__ invalid_control ; 
 struct cleanup* make_cleanup_free_command_lines (struct command_line**) ; 
 scalar_t__ recurse_read_control_structure (struct command_line*) ; 
 int /*<<< orphan*/  warning (char*) ; 

__attribute__((used)) static struct command_line *
get_command_line (enum command_control_type type, char *arg)
{
  struct command_line *cmd;
  struct cleanup *old_chain = NULL;

  /* Allocate and build a new command line structure.  */
  cmd = build_command_line (type, arg);

  old_chain = make_cleanup_free_command_lines (&cmd);

  /* Read in the body of this command.  */
  if (recurse_read_control_structure (cmd) == invalid_control)
    {
      warning ("error reading in control structure\n");
      do_cleanups (old_chain);
      return NULL;
    }

  discard_cleanups (old_chain);
  return cmd;
}