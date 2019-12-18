#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {size_t httpVersion; size_t httpKeepAlive; } ;
struct TYPE_11__ {char* lst; char* buf; } ;
typedef  TYPE_1__ JsonBuf ;
typedef  int /*<<< orphan*/  HttpSqlCmd ;
typedef  TYPE_2__ HttpContext ;

/* Variables and functions */
 size_t HTTP_RESPONSE_GRAFANA ; 
 int /*<<< orphan*/  JsonObjEnd ; 
 int /*<<< orphan*/  JsonObjStt ; 
 int /*<<< orphan*/  httpInitJsonBuf (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  httpJsonPair (TYPE_1__*,char*,int,char*,int) ; 
 int /*<<< orphan*/  httpJsonToken (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * httpKeepAliveStr ; 
 TYPE_1__* httpMallocJsonBuf (TYPE_2__*) ; 
 char** httpRespTemplate ; 
 int /*<<< orphan*/ * httpVersionStr ; 
 int /*<<< orphan*/  httpWriteBuf (TYPE_2__*,char*,int) ; 
 int sprintf (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strlen (char*) ; 

void gcSendHeartBeatResp(HttpContext *pContext, HttpSqlCmd *cmd) {
  JsonBuf *jsonBuf = httpMallocJsonBuf(pContext);
  if (jsonBuf == NULL) return;

  char *desc = "Grafana server receive a quest from you!";

  httpInitJsonBuf(jsonBuf, pContext);

  httpJsonToken(jsonBuf, JsonObjStt);
  httpJsonPair(jsonBuf, "message", (int)strlen("message"), desc, (int)strlen(desc));
  httpJsonToken(jsonBuf, JsonObjEnd);

  char head[1024];

  int hLen = sprintf(head, httpRespTemplate[HTTP_RESPONSE_GRAFANA], httpVersionStr[pContext->httpVersion],
                     httpKeepAliveStr[pContext->httpKeepAlive], (jsonBuf->lst - jsonBuf->buf));
  httpWriteBuf(pContext, head, hLen);
  httpWriteBuf(pContext, jsonBuf->buf, (int)(jsonBuf->lst - jsonBuf->buf));
}