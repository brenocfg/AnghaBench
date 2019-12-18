#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* encodeMethod; int /*<<< orphan*/  user; int /*<<< orphan*/  ipstr; int /*<<< orphan*/  fd; TYPE_1__* multiCmds; struct TYPE_11__* signature; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* initJsonFp ) (TYPE_3__*) ;} ;
struct TYPE_9__ {scalar_t__ size; scalar_t__ pos; } ;
typedef  TYPE_1__ HttpSqlCmds ;
typedef  TYPE_2__ HttpEncodeMethod ;
typedef  TYPE_3__ HttpContext ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP_INVALID_MULTI_REQUEST ; 
 int /*<<< orphan*/  httpProcessMultiSql (TYPE_3__*) ; 
 int /*<<< orphan*/  httpSendErrorResp (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpTrace (char*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

void httpProcessMultiSqlCmd(HttpContext *pContext) {
  if (pContext == NULL || pContext->signature != pContext) return;

  HttpSqlCmds *multiCmds = pContext->multiCmds;
  if (multiCmds == NULL || multiCmds->size <= 0 || multiCmds->pos >= multiCmds->size || multiCmds->pos < 0) {
    httpSendErrorResp(pContext, HTTP_INVALID_MULTI_REQUEST);
    return;
  }

  httpTrace("context:%p, fd:%d, ip:%s, user:%s, start multi-querys pos:%d, size:%d", pContext, pContext->fd,
            pContext->ipstr, pContext->user, multiCmds->pos, multiCmds->size);
  HttpEncodeMethod *encode = pContext->encodeMethod;
  if (encode->initJsonFp) {
    (encode->initJsonFp)(pContext);
  }

  httpProcessMultiSql(pContext);
}