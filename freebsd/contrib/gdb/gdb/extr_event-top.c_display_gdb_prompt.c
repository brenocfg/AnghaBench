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
 scalar_t__ alloca (int) ; 
 scalar_t__ async_command_editing_p ; 
 int /*<<< orphan*/  current_interp_display_prompt_p () ; 
 int /*<<< orphan*/  fputs_unfiltered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 char* get_prompt () ; 
 int /*<<< orphan*/  input_handler ; 
 int /*<<< orphan*/  rl_callback_handler_install (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rl_callback_handler_remove () ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ sync_execution ; 
 scalar_t__ target_executing ; 

void
display_gdb_prompt (char *new_prompt)
{
  int prompt_length = 0;
  char *gdb_prompt = get_prompt ();

  /* Each interpreter has its own rules on displaying the command
     prompt.  */
  if (!current_interp_display_prompt_p ())
    return;

  if (target_executing && sync_execution)
    {
      /* This is to trick readline into not trying to display the
         prompt.  Even though we display the prompt using this
         function, readline still tries to do its own display if we
         don't call rl_callback_handler_install and
         rl_callback_handler_remove (which readline detects because a
         global variable is not set). If readline did that, it could
         mess up gdb signal handlers for SIGINT.  Readline assumes
         that between calls to rl_set_signals and rl_clear_signals gdb
         doesn't do anything with the signal handlers. Well, that's
         not the case, because when the target executes we change the
         SIGINT signal handler. If we allowed readline to display the
         prompt, the signal handler change would happen exactly
         between the calls to the above two functions.
         Calling rl_callback_handler_remove(), does the job. */

      rl_callback_handler_remove ();
      return;
    }

  if (!new_prompt)
    {
      /* Just use the top of the prompt stack. */
      prompt_length = strlen (PREFIX (0)) +
	strlen (SUFFIX (0)) +
	strlen (gdb_prompt) + 1;

      new_prompt = (char *) alloca (prompt_length);

      /* Prefix needs to have new line at end. */
      strcpy (new_prompt, PREFIX (0));
      strcat (new_prompt, gdb_prompt);
      /* Suffix needs to have a new line at end and \032 \032 at
         beginning. */
      strcat (new_prompt, SUFFIX (0));
    }

  if (async_command_editing_p)
    {
      rl_callback_handler_remove ();
      rl_callback_handler_install (new_prompt, input_handler);
    }
  /* new_prompt at this point can be the top of the stack or the one passed in */
  else if (new_prompt)
    {
      /* Don't use a _filtered function here.  It causes the assumed
         character position to be off, since the newline we read from
         the user is not accounted for.  */
      fputs_unfiltered (new_prompt, gdb_stdout);
      gdb_flush (gdb_stdout);
    }
}