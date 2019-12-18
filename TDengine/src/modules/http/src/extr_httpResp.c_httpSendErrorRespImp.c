#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t httpVersion; size_t httpKeepAlive; int /*<<< orphan*/  ipstr; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ HttpContext ;

/* Variables and functions */
 size_t HTTP_RESPONSE_ERROR ; 
 size_t HTTP_RESPONSE_JSON_ERROR ; 
 int /*<<< orphan*/  httpCloseContextByApp (TYPE_1__*) ; 
 int /*<<< orphan*/  httpError (char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char*) ; 
 int /*<<< orphan*/ * httpKeepAliveStr ; 
 char** httpRespTemplate ; 
 int /*<<< orphan*/ * httpVersionStr ; 
 int /*<<< orphan*/  httpWriteBuf (TYPE_1__*,char*,int) ; 
 int sprintf (char*,char*,int,...) ; 

void httpSendErrorRespImp(HttpContext *pContext, int httpCode, char *httpCodeStr, int errNo, char *desc) {
  httpError("context:%p, fd:%d, ip:%s, code:%d, error:%d:%s", pContext, pContext->fd, pContext->ipstr, httpCode, errNo,
            desc);

  char head[512] = {0};
  char body[512] = {0};

  int bodyLen = sprintf(body, httpRespTemplate[HTTP_RESPONSE_JSON_ERROR], errNo, desc);
  int headLen = sprintf(head, httpRespTemplate[HTTP_RESPONSE_ERROR], httpVersionStr[pContext->httpVersion], httpCode,
                        httpCodeStr, httpKeepAliveStr[pContext->httpKeepAlive], bodyLen);

  httpWriteBuf(pContext, head, headLen);
  httpWriteBuf(pContext, body, bodyLen);
  httpCloseContextByApp(pContext);
}