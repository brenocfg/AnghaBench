#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_6__ {TYPE_1__* multiCmds; } ;
struct TYPE_5__ {char* buffer; int bufferPos; int bufferSize; } ;
typedef  TYPE_1__ HttpSqlCmds ;
typedef  TYPE_2__ HttpContext ;

/* Variables and functions */
 int /*<<< orphan*/  httpReMallocMultiCmdsBuffer (TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 

int32_t httpAddToSqlCmdBufferWithSize(HttpContext *pContext, int mallocSize) {
  HttpSqlCmds *cmd = pContext->multiCmds;
  if (cmd->buffer == NULL) return -1;

  if (cmd->bufferPos + mallocSize >= cmd->bufferSize) {
    if (!httpReMallocMultiCmdsBuffer(pContext, cmd->bufferSize * 2)) return -1;
  }

  char *buffer = cmd->buffer + cmd->bufferPos;
  memset(cmd->buffer + cmd->bufferPos, 0, (size_t)mallocSize);
  cmd->bufferPos = cmd->bufferPos + mallocSize;

  return (int32_t)(buffer - cmd->buffer);
}