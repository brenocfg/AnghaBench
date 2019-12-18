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
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_4__ {scalar_t__ cursorOffset; scalar_t__ commandSize; scalar_t__ endOffset; scalar_t__ screenOffset; scalar_t__ command; } ;
typedef  TYPE_1__ Command ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  clearScreen (scalar_t__,scalar_t__) ; 
 scalar_t__ mbtowc (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ prompt_size ; 
 int /*<<< orphan*/  showOnScreen (TYPE_1__*) ; 
 scalar_t__ wcwidth (int /*<<< orphan*/ ) ; 

void insertChar(Command *cmd, char *c, int size) {
  assert(cmd->cursorOffset <= cmd->commandSize && cmd->endOffset >= cmd->screenOffset);

  wchar_t wc;
  if (mbtowc(&wc, c, size) < 0) return;

  clearScreen(cmd->endOffset + prompt_size, cmd->screenOffset + prompt_size);
  /* update the buffer */
  memmove(cmd->command + cmd->cursorOffset + size, cmd->command + cmd->cursorOffset,
          cmd->commandSize - cmd->cursorOffset);
  memcpy(cmd->command + cmd->cursorOffset, c, size);
  /* update the values */
  cmd->commandSize += size;
  cmd->cursorOffset += size;
  cmd->screenOffset += wcwidth(wc);
  cmd->endOffset += wcwidth(wc);
  showOnScreen(cmd);
}