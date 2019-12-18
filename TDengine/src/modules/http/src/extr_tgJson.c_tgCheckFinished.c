#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct HttpContext {int /*<<< orphan*/  ipstr; int /*<<< orphan*/  fd; TYPE_2__* multiCmds; } ;
typedef  void* int16_t ;
struct TYPE_7__ {scalar_t__ cmdState; scalar_t__ cmdType; int /*<<< orphan*/  tagNum; int /*<<< orphan*/  cmdReturnType; } ;
struct TYPE_6__ {int pos; TYPE_1__* cmds; } ;
struct TYPE_5__ {scalar_t__ cmdState; } ;
typedef  TYPE_2__ HttpSqlCmds ;
typedef  TYPE_3__ HttpSqlCmd ;

/* Variables and functions */
 scalar_t__ HTTP_CMD_STATE_NOT_RUN_YET ; 
 void* HTTP_CMD_STATE_RUN_FINISHED ; 
 scalar_t__ HTTP_CMD_TYPE_CREATE_DB ; 
 scalar_t__ HTTP_CMD_TYPE_CREATE_STBALE ; 
 scalar_t__ HTTP_CMD_TYPE_INSERT ; 
 int TSDB_CODE_DB_NOT_SELECTED ; 
 int TSDB_CODE_INVALID_DB ; 
 int TSDB_CODE_INVALID_TABLE ; 
 int /*<<< orphan*/  httpTrace (char*,struct HttpContext*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

bool tgCheckFinished(struct HttpContext *pContext, HttpSqlCmd *cmd, int code) {
  HttpSqlCmds *multiCmds = pContext->multiCmds;
  httpTrace("context:%p, fd:%d, ip:%s, check telegraf command, code:%d, state:%d, type:%d, rettype:%d, tags:%d",
            pContext, pContext->fd, pContext->ipstr, code, cmd->cmdState, cmd->cmdType, cmd->cmdReturnType, cmd->tagNum);

  if (cmd->cmdType == HTTP_CMD_TYPE_INSERT) {
    if (cmd->cmdState == HTTP_CMD_STATE_NOT_RUN_YET) {
      if (code == TSDB_CODE_DB_NOT_SELECTED || code == TSDB_CODE_INVALID_DB) {
        cmd->cmdState = HTTP_CMD_STATE_RUN_FINISHED;
        if (multiCmds->cmds[0].cmdState == HTTP_CMD_STATE_NOT_RUN_YET) {
          multiCmds->pos = (int16_t)-1;
          httpTrace("context:%p, fd:%d, ip:%s, import failed, try create database", pContext, pContext->fd,
                    pContext->ipstr);
          return false;
        }
      } else if (code == TSDB_CODE_INVALID_TABLE) {
        cmd->cmdState = HTTP_CMD_STATE_RUN_FINISHED;
        if (multiCmds->cmds[multiCmds->pos - 1].cmdState == HTTP_CMD_STATE_NOT_RUN_YET) {
          multiCmds->pos = (int16_t)(multiCmds->pos - 2);
          httpTrace("context:%p, fd:%d, ip:%s, import failed, try create stable", pContext, pContext->fd,
                    pContext->ipstr);
          return false;
        }
      } else {
      }
    } else {
    }
  } else if (cmd->cmdType == HTTP_CMD_TYPE_CREATE_DB) {
    cmd->cmdState = HTTP_CMD_STATE_RUN_FINISHED;
    httpTrace("context:%p, fd:%d, ip:%s, code:%d, create database failed", pContext, pContext->fd, pContext->ipstr,
              code);
  } else if (cmd->cmdType == HTTP_CMD_TYPE_CREATE_STBALE) {
    cmd->cmdState = HTTP_CMD_STATE_RUN_FINISHED;
    httpTrace("context:%p, fd:%d, ip:%s, code:%d, create stable failed", pContext, pContext->fd, pContext->ipstr, code);
  } else {
  }

  return true;
}