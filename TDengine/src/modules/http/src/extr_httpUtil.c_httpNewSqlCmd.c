#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* multiCmds; } ;
struct TYPE_8__ {int /*<<< orphan*/  cmdState; int /*<<< orphan*/  cmdReturnType; int /*<<< orphan*/  cmdType; } ;
struct TYPE_7__ {int size; int maxSize; TYPE_2__* cmds; } ;
typedef  TYPE_1__ HttpSqlCmds ;
typedef  TYPE_2__ HttpSqlCmd ;
typedef  TYPE_3__ HttpContext ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP_CMD_RETURN_TYPE_WITH_RETURN ; 
 int /*<<< orphan*/  HTTP_CMD_STATE_NOT_RUN_YET ; 
 int /*<<< orphan*/  HTTP_CMD_TYPE_UN_SPECIFIED ; 
 int /*<<< orphan*/  httpReMallocMultiCmdsSize (TYPE_3__*,int) ; 

HttpSqlCmd *httpNewSqlCmd(HttpContext *pContext) {
  HttpSqlCmds *multiCmds = pContext->multiCmds;
  if (multiCmds->size >= multiCmds->maxSize) {
    if (!httpReMallocMultiCmdsSize(pContext, 2 * multiCmds->maxSize)) return NULL;
  }

  HttpSqlCmd *cmd = multiCmds->cmds + multiCmds->size++;
  cmd->cmdType = HTTP_CMD_TYPE_UN_SPECIFIED;
  cmd->cmdReturnType = HTTP_CMD_RETURN_TYPE_WITH_RETURN;
  cmd->cmdState = HTTP_CMD_STATE_NOT_RUN_YET;

  return cmd;
}