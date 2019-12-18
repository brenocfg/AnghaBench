#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  user; int /*<<< orphan*/  ipstr; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ HttpContext ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP_GEN_TAOSD_TOKEN_ERR ; 
 int /*<<< orphan*/  httpGenTaosdAuthToken (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  httpSendErrorResp (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpSendSuccResp (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  httpTrace (char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

void httpProcessLoginCmd(HttpContext *pContext) {
  char token[128] = {0};
  if (!httpGenTaosdAuthToken(pContext, token, 128)) {
    httpSendErrorResp(pContext, HTTP_GEN_TAOSD_TOKEN_ERR);
  } else {
    httpTrace("context:%p, fd:%d, ip:%s, user:%s, login via http, return token:%s",
              pContext, pContext->fd, pContext->ipstr, pContext->user, token);
    httpSendSuccResp(pContext, token);
  }
}