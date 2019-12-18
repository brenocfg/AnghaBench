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
struct TYPE_4__ {scalar_t__ cursorOffset; scalar_t__ commandSize; scalar_t__ endOffset; scalar_t__ screenOffset; scalar_t__ command; } ;
typedef  TYPE_1__ Command ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  clearScreen (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  getPrevCharSize (scalar_t__,scalar_t__,int*,int*) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ prompt_size ; 
 int /*<<< orphan*/  showOnScreen (TYPE_1__*) ; 

void backspaceChar(Command *cmd) {
  assert(cmd->cursorOffset <= cmd->commandSize && cmd->endOffset >= cmd->screenOffset);

  if (cmd->cursorOffset > 0) {
    clearScreen(cmd->endOffset + prompt_size, cmd->screenOffset + prompt_size);
    int size = 0;
    int width = 0;
    getPrevCharSize(cmd->command, cmd->cursorOffset, &size, &width);
    memmove(cmd->command + cmd->cursorOffset - size, cmd->command + cmd->cursorOffset,
            cmd->commandSize - cmd->cursorOffset);
    cmd->commandSize -= size;
    cmd->cursorOffset -= size;
    cmd->screenOffset -= width;
    cmd->endOffset -= width;
    showOnScreen(cmd);
  }
}