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
 scalar_t__ async_command_editing_p ; 
 int /*<<< orphan*/  call_readline ; 
 int /*<<< orphan*/  command_line_handler ; 
 int /*<<< orphan*/  gdb_readline2 ; 
 int /*<<< orphan*/  input_handler ; 
 int /*<<< orphan*/  rl_callback_handler_remove () ; 
 int /*<<< orphan*/  rl_callback_read_char_wrapper ; 

__attribute__((used)) static void
change_line_handler (void)
{
  /* NOTE: this operates on input_fd, not instream. If we are reading
     commands from a file, instream will point to the file. However in
     async mode, we always read commands from a file with editing
     off. This means that the 'set editing on/off' will have effect
     only on the interactive session. */

  if (async_command_editing_p)
    {
      /* Turn on editing by using readline. */
      call_readline = rl_callback_read_char_wrapper;
      input_handler = command_line_handler;
    }
  else
    {
      /* Turn off editing by using gdb_readline2. */
      rl_callback_handler_remove ();
      call_readline = gdb_readline2;

      /* Set up the command handler as well, in case we are called as
         first thing from .gdbinit. */
      input_handler = command_line_handler;
    }
}