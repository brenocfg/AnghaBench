#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_6__ {char* buffer; char* command; } ;
typedef  int /*<<< orphan*/  TAOS ;
typedef  TYPE_1__ Command ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_COMMAND_SIZE ; 
 scalar_t__ calloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char getchar () ; 
 int /*<<< orphan*/  insertChar (TYPE_1__*,char) ; 
 int /*<<< orphan*/  isReadyGo (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  shellPrintContinuePrompt () ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  updateBuffer (TYPE_1__*) ; 

void shellReadCommand(TAOS *con, char command[]) {
  Command cmd;
  memset(&cmd, 0, sizeof(cmd));
  cmd.buffer = (char *)calloc(1, MAX_COMMAND_SIZE);
  cmd.command = (char *)calloc(1, MAX_COMMAND_SIZE);

  // Read input.
  char c;
  while (1) {
    c = getchar();

    switch (c) {
      case '\n':
      case '\r':
        if (isReadyGo(&cmd)) {
          sprintf(command, "%s%s", cmd.buffer, cmd.command);
          free(cmd.buffer);
          cmd.buffer = NULL;
          free(cmd.command);
          cmd.command = NULL;
          return;
        } else {
          shellPrintContinuePrompt();
          updateBuffer(&cmd);
        }
        break;
      default:
        insertChar(&cmd, c);
    }
  }
}