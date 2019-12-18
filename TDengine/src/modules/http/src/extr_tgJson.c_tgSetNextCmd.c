#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct HttpContext {int /*<<< orphan*/  ipstr; int /*<<< orphan*/  fd; TYPE_1__* multiCmds; } ;
typedef  scalar_t__ int16_t ;
struct TYPE_5__ {int /*<<< orphan*/  cmdType; int /*<<< orphan*/  tagNum; int /*<<< orphan*/  cmdReturnType; int /*<<< orphan*/  cmdState; } ;
struct TYPE_4__ {scalar_t__ pos; } ;
typedef  TYPE_1__ HttpSqlCmds ;
typedef  TYPE_2__ HttpSqlCmd ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP_CMD_TYPE_CREATE_DB ; 
 int /*<<< orphan*/  HTTP_CMD_TYPE_CREATE_STBALE ; 
 int /*<<< orphan*/  HTTP_CMD_TYPE_INSERT ; 
 int /*<<< orphan*/  httpTrace (char*,struct HttpContext*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void tgSetNextCmd(struct HttpContext *pContext, HttpSqlCmd *cmd, int code) {
  HttpSqlCmds *multiCmds = pContext->multiCmds;
  httpTrace("context:%p, fd:%d, ip:%s, get telegraf next command, pos:%d, code:%d, state:%d, type:%d, rettype:%d, tags:%d",
            pContext, pContext->fd, pContext->ipstr, multiCmds->pos, code, cmd->cmdState, cmd->cmdType,
            cmd->cmdReturnType, cmd->tagNum);

  if (cmd->cmdType == HTTP_CMD_TYPE_INSERT) {
    multiCmds->pos = (int16_t)(multiCmds->pos + 2);
  } else if (cmd->cmdType == HTTP_CMD_TYPE_CREATE_DB) {
    multiCmds->pos++;
  } else if (cmd->cmdType == HTTP_CMD_TYPE_CREATE_STBALE) {
    multiCmds->pos++;
  } else {
    multiCmds->pos++;
  }
}