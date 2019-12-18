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
typedef  int int16_t ;
struct TYPE_6__ {int /*<<< orphan*/  user; int /*<<< orphan*/  ipstr; int /*<<< orphan*/  fd; TYPE_1__* multiCmds; } ;
struct TYPE_5__ {int maxSize; int /*<<< orphan*/ * cmds; } ;
typedef  TYPE_1__ HttpSqlCmds ;
typedef  int /*<<< orphan*/  HttpSqlCmd ;
typedef  TYPE_2__ HttpContext ;

/* Variables and functions */
 int HTTP_MAX_CMD_SIZE ; 
 int /*<<< orphan*/  httpError (char*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ realloc (int /*<<< orphan*/ *,size_t) ; 

bool httpReMallocMultiCmdsSize(HttpContext *pContext, int cmdSize) {
  HttpSqlCmds *multiCmds = pContext->multiCmds;

  if (cmdSize > HTTP_MAX_CMD_SIZE) {
    httpError("context:%p, fd:%d, ip:%s, user:%s, mulitcmd size:%d large then %d", pContext, pContext->fd,
              pContext->ipstr, pContext->user, cmdSize, HTTP_MAX_CMD_SIZE);
    return false;
  }

  multiCmds->cmds = (HttpSqlCmd *)realloc(multiCmds->cmds, (size_t)cmdSize * sizeof(HttpSqlCmd));
  if (multiCmds->cmds == NULL) {
    httpError("context:%p, fd:%d, ip:%s, user:%s, malloc cmds:%d error", pContext, pContext->fd, pContext->ipstr,
              pContext->user, cmdSize);
    return false;
  }
  memset(multiCmds->cmds + multiCmds->maxSize * (int16_t)sizeof(HttpSqlCmd), 0,
         (size_t)(cmdSize - multiCmds->maxSize) * sizeof(HttpSqlCmd));
  multiCmds->maxSize = (int16_t)cmdSize;

  return true;
}