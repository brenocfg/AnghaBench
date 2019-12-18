#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  pos; } ;
struct TYPE_15__ {TYPE_3__* path; TYPE_2__ method; TYPE_6__* pMethod; } ;
struct TYPE_17__ {int /*<<< orphan*/  ipstr; int /*<<< orphan*/  fd; TYPE_1__* pThread; TYPE_5__ parser; } ;
struct TYPE_16__ {int /*<<< orphan*/  module; } ;
struct TYPE_14__ {int methodScannerLen; TYPE_6__** methodScanner; } ;
struct TYPE_13__ {int /*<<< orphan*/  pos; } ;
struct TYPE_11__ {TYPE_4__* pServer; } ;
typedef  TYPE_4__ HttpServer ;
typedef  TYPE_5__ HttpParser ;
typedef  TYPE_6__ HttpDecodeMethod ;
typedef  TYPE_7__ HttpContext ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP_UNSUPPORT_URL ; 
 int /*<<< orphan*/  httpError (char*,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpSendErrorResp (TYPE_7__*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool httpGetDecodeMethod(HttpContext* pContext) {
  HttpParser* pParser = &pContext->parser;

  HttpServer* pServer = pContext->pThread->pServer;
  int         methodLen = pServer->methodScannerLen;
  for (int i = 0; i < methodLen; i++) {
    HttpDecodeMethod* method = pServer->methodScanner[i];
    if (strcmp(method->module, pParser->path[0].pos) != 0) {
      continue;
    }
    pParser->pMethod = method;
    return true;
  }

  httpError("context:%p, fd:%d, ip:%s, error:the url is not support, method:%s, path:%s",
            pContext, pContext->fd, pContext->ipstr, pParser->method.pos, pParser->path[0].pos);
  httpSendErrorResp(pContext, HTTP_UNSUPPORT_URL);

  return false;
}