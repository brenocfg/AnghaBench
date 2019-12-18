#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ cursorOffset; char* command; } ;
typedef  TYPE_1__ Command ;

/* Variables and functions */
 scalar_t__ MAX_COMMAND_SIZE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  stdout ; 

void insertChar(Command *cmd, char c) {
  // TODO: Check if the length enough.
  if (cmd->cursorOffset >= MAX_COMMAND_SIZE) {
    fprintf(stdout, "sql is larger than %d bytes", MAX_COMMAND_SIZE);
    return;
  }

  cmd->command[cmd->cursorOffset++] = c;
}