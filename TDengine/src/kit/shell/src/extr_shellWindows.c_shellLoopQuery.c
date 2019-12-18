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
 char* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shellPrintPrompt () ; 
 int /*<<< orphan*/  shellReadCommand (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  shellRunCommand (int /*<<< orphan*/ *,char*) ; 

void *shellLoopQuery(void *arg) {
  TAOS *con = (TAOS *)arg;
  char *command = malloc(MAX_COMMAND_SIZE);
  if (command == NULL) return NULL;

  while (1) {
    memset(command, 0, MAX_COMMAND_SIZE);
    shellPrintPrompt();

    // Read command from shell.
    shellReadCommand(con, command);

    // Run the command
    shellRunCommand(con, command);
  }

  return NULL;
}