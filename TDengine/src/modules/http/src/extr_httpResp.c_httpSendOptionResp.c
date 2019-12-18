#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t httpVersion; size_t httpKeepAlive; } ;
typedef  TYPE_1__ HttpContext ;

/* Variables and functions */
 size_t HTTP_RESPONSE_JSON_OK ; 
 size_t HTTP_RESPONSE_OPTIONS ; 
 int /*<<< orphan*/  HTTP_SUCCESS ; 
 int /*<<< orphan*/  httpCloseContextByApp (TYPE_1__*) ; 
 int /*<<< orphan*/ * httpKeepAliveStr ; 
 char** httpRespTemplate ; 
 int /*<<< orphan*/ * httpVersionStr ; 
 int /*<<< orphan*/  httpWriteBuf (TYPE_1__*,char*,int) ; 
 int sprintf (char*,char*,int /*<<< orphan*/ ,char*,...) ; 

void httpSendOptionResp(HttpContext *pContext, char *desc) {
  char head[1024] = {0};
  char body[1024] = {0};

  int bodyLen = sprintf(body, httpRespTemplate[HTTP_RESPONSE_JSON_OK], HTTP_SUCCESS, desc);
  int headLen = sprintf(head, httpRespTemplate[HTTP_RESPONSE_OPTIONS], httpVersionStr[pContext->httpVersion],
                        httpKeepAliveStr[pContext->httpKeepAlive], bodyLen);

  httpWriteBuf(pContext, head, headLen);
  httpWriteBuf(pContext, body, bodyLen);
  httpCloseContextByApp(pContext);
}