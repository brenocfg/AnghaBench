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
 scalar_t__ ISATTY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_file_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int async_command_editing_p ; 
 int /*<<< orphan*/  call_readline ; 
 int /*<<< orphan*/  command_line_handler ; 
 scalar_t__ event_loop_p ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_readline2 ; 
 void* gdb_stderr ; 
 void* gdb_stdlog ; 
 void* gdb_stdout ; 
 void* gdb_stdtarg ; 
 int /*<<< orphan*/  input_fd ; 
 int /*<<< orphan*/  input_handler ; 
 int /*<<< orphan*/  instream ; 
 int /*<<< orphan*/  rl_callback_read_char_wrapper ; 
 int /*<<< orphan*/  rl_instream ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin_event_handler ; 
 void* stdio_fileopen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

void
gdb_setup_readline (void)
{
  /* This function is a noop for the sync case.  The assumption is that
     the sync setup is ALL done in gdb_init, and we would only mess it up
     here.  The sync stuff should really go away over time. */

  if (event_loop_p)
    {
      gdb_stdout = stdio_fileopen (stdout);
      gdb_stderr = stdio_fileopen (stderr);
      gdb_stdlog = gdb_stderr;  /* for moment */
      gdb_stdtarg = gdb_stderr; /* for moment */

      /* If the input stream is connected to a terminal, turn on
         editing.  */
      if (ISATTY (instream))
	{
	  /* Tell gdb that we will be using the readline library. This
	     could be overwritten by a command in .gdbinit like 'set
	     editing on' or 'off'. */
	  async_command_editing_p = 1;
	  
	  /* When a character is detected on instream by select or
	     poll, readline will be invoked via this callback
	     function. */
	  call_readline = rl_callback_read_char_wrapper;
	}
      else
	{
	  async_command_editing_p = 0;
	  call_readline = gdb_readline2;
	}

      /* When readline has read an end-of-line character, it passes
         the complete line to gdb for processing. command_line_handler
         is the function that does this. */
      input_handler = command_line_handler;

      /* Tell readline to use the same input stream that gdb uses. */
      rl_instream = instream;

      /* Get a file descriptor for the input stream, so that we can
         register it with the event loop. */
      input_fd = fileno (instream);

      /* Now we need to create the event sources for the input file
         descriptor. */
      /* At this point in time, this is the only event source that we
         register with the even loop. Another source is going to be
         the target program (inferior), but that must be registered
         only when it actually exists (I.e. after we say 'run' or
         after we connect to a remote target. */
      add_file_handler (input_fd, stdin_event_handler, 0);
    }
}