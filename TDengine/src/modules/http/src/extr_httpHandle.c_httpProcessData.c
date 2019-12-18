#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  pos; } ;
struct TYPE_12__ {TYPE_1__ method; } ;
struct TYPE_13__ {int /*<<< orphan*/  ipstr; int /*<<< orphan*/  fd; TYPE_2__ parser; int /*<<< orphan*/  state; } ;
typedef  TYPE_3__ HttpContext ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP_CONTEXT_STATE_HANDLING ; 
 int /*<<< orphan*/  HTTP_CONTEXT_STATE_READY ; 
 int /*<<< orphan*/  httpAlterContextState (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpCloseContextByApp (TYPE_3__*) ; 
 int /*<<< orphan*/  httpContextStateStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpDecodeRequest (TYPE_3__*) ; 
 int /*<<< orphan*/  httpProcessRequest (TYPE_3__*) ; 
 int /*<<< orphan*/  httpSendOptionResp (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  httpTrace (char*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

bool httpProcessData(HttpContext* pContext) {

  if (!httpAlterContextState(pContext, HTTP_CONTEXT_STATE_READY, HTTP_CONTEXT_STATE_HANDLING)) {
    httpTrace("context:%p, fd:%d, ip:%s, state:%s not in ready state, stop process request",
            pContext, pContext->fd, pContext->ipstr, httpContextStateStr(pContext->state));
    httpCloseContextByApp(pContext);
    return false;
  }

  // handle Cross-domain request
  if (strcmp(pContext->parser.method.pos, "OPTIONS") == 0) {
    httpTrace("context:%p, fd:%d, ip:%s, process options request", pContext, pContext->fd, pContext->ipstr);
    httpSendOptionResp(pContext, "process options request success");
  } else {
    if (!httpDecodeRequest(pContext)) {
      /*
       * httpCloseContextByApp has been called when parsing the error
       */
      //httpCloseContextByApp(pContext);
    } else {
      httpProcessRequest(pContext);
    }
  }

  return true;
}