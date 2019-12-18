#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ cursorOffset; scalar_t__ commandSize; scalar_t__ endOffset; scalar_t__ screenOffset; char* buffer; char* command; int /*<<< orphan*/  bufferSize; } ;
typedef  TYPE_1__ Command ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_COMMAND_SIZE ; 
 int /*<<< orphan*/  REG_EXTENDED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ regex_match (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  showOnScreen (TYPE_1__*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

void updateBuffer(Command *cmd) {
  assert(cmd->cursorOffset <= cmd->commandSize && cmd->endOffset >= cmd->screenOffset);

  if (regex_match(cmd->buffer, "(\\s+$)|(^$)", REG_EXTENDED)) strcat(cmd->command, " ");
  strcat(cmd->buffer, cmd->command);
  cmd->bufferSize += cmd->commandSize;

  memset(cmd->command, 0, MAX_COMMAND_SIZE);
  cmd->cursorOffset = 0;
  cmd->screenOffset = 0;
  cmd->commandSize = 0;
  cmd->endOffset = 0;
  showOnScreen(cmd);
}