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
 int /*<<< orphan*/  logging_filename ; 
 scalar_t__ logging_overwrite ; 
 scalar_t__ logging_redirect ; 
 int /*<<< orphan*/  printf_unfiltered (char*,...) ; 
 int /*<<< orphan*/ * saved_filename ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
show_logging_command (char *args, int from_tty)
{
  if (saved_filename)
    printf_unfiltered ("Currently logging to \"%s\".\n", saved_filename);
  if (saved_filename == NULL
      || strcmp (logging_filename, saved_filename) != 0)
    printf_unfiltered ("Future logs will be written to %s.\n",
		       logging_filename);

  if (logging_overwrite)
    printf_unfiltered ("Logs will overwrite the log file.\n");
  else
    printf_unfiltered ("Logs will be appended to the log file.\n");

  if (logging_redirect)
    printf_unfiltered ("Output will be sent only to the log file.\n");
  else
    printf_unfiltered ("Output will be logged and displayed.\n");
}