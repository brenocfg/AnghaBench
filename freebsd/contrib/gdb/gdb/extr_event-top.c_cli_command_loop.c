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
 char* PREFIX (int /*<<< orphan*/ ) ; 
 char* SUFFIX (int /*<<< orphan*/ ) ; 
 scalar_t__ async_command_editing_p ; 
 int /*<<< orphan*/  display_gdb_prompt (int /*<<< orphan*/ ) ; 
 char* get_prompt () ; 
 int /*<<< orphan*/  input_handler ; 
 int /*<<< orphan*/  rl_callback_handler_install (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_event_loop () ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ xmalloc (int) ; 

void
cli_command_loop (void)
{
  int length;
  char *a_prompt;
  char *gdb_prompt = get_prompt ();

  /* If we are using readline, set things up and display the first
     prompt, otherwise just print the prompt. */
  if (async_command_editing_p)
    {
      /* Tell readline what the prompt to display is and what function it
         will need to call after a whole line is read. This also displays
         the first prompt. */
      length = strlen (PREFIX (0)) + strlen (gdb_prompt) + strlen (SUFFIX (0)) + 1;
      a_prompt = (char *) xmalloc (length);
      strcpy (a_prompt, PREFIX (0));
      strcat (a_prompt, gdb_prompt);
      strcat (a_prompt, SUFFIX (0));
      rl_callback_handler_install (a_prompt, input_handler);
    }
  else
    display_gdb_prompt (0);

  /* Now it's time to start the event loop. */
  start_event_loop ();
}