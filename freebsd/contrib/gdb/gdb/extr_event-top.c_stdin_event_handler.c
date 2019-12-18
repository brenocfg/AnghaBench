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
typedef  int /*<<< orphan*/  gdb_client_data ;

/* Variables and functions */
 int /*<<< orphan*/  call_readline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_file_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  discard_all_continuations () ; 
 int /*<<< orphan*/  input_fd ; 
 scalar_t__ instream ; 
 int /*<<< orphan*/  printf_unfiltered (char*) ; 
 int /*<<< orphan*/  quit_command (char*,int) ; 
 scalar_t__ stdin ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void
stdin_event_handler (int error, gdb_client_data client_data)
{
  if (error)
    {
      printf_unfiltered ("error detected on stdin\n");
      delete_file_handler (input_fd);
      discard_all_continuations ();
      /* If stdin died, we may as well kill gdb. */
      quit_command ((char *) 0, stdin == instream);
    }
  else
    (*call_readline) (client_data);
}