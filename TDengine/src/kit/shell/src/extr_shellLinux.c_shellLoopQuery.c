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
typedef  int /*<<< orphan*/  TAOS ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_COMMAND_SIZE ; 
 int /*<<< orphan*/  cleanup_handler ; 
 int /*<<< orphan*/  get_old_terminal_mode (int /*<<< orphan*/ *) ; 
 scalar_t__ indicator ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oldtio ; 
 int /*<<< orphan*/  pthread_cleanup_pop (int) ; 
 int /*<<< orphan*/  pthread_cleanup_push (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_terminal_mode () ; 
 int /*<<< orphan*/  set_terminal_mode () ; 
 int /*<<< orphan*/  shellReadCommand (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  shellRunCommand (int /*<<< orphan*/ *,char*) ; 

void *shellLoopQuery(void *arg) {
  if (indicator) {
    get_old_terminal_mode(&oldtio);
    indicator = 0;
  }

  TAOS *con = (TAOS *)arg;

  pthread_cleanup_push(cleanup_handler, NULL);

  char *command = malloc(MAX_COMMAND_SIZE);

  while (1) {
    // Read command from shell.

    memset(command, 0, MAX_COMMAND_SIZE);
    set_terminal_mode();
    shellReadCommand(con, command);
    reset_terminal_mode();

    if (command != NULL) {
      // Run the command
      shellRunCommand(con, command);
    }
  }

  pthread_cleanup_pop(1);

  return NULL;
}