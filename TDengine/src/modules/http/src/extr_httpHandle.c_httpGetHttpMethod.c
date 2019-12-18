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
typedef  size_t int16_t ;
struct TYPE_7__ {char* pos; size_t len; } ;
struct TYPE_8__ {char* pLast; TYPE_1__ method; } ;
struct TYPE_9__ {int /*<<< orphan*/  ipstr; int /*<<< orphan*/  fd; TYPE_2__ parser; } ;
typedef  TYPE_2__ HttpParser ;
typedef  TYPE_3__ HttpContext ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP_PARSE_HTTP_METHOD_ERROR ; 
 int /*<<< orphan*/  httpSendErrorResp (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpTrace (char*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 char* strchr (char*,char) ; 

bool httpGetHttpMethod(HttpContext* pContext) {
  HttpParser* pParser = &pContext->parser;

  char*       pSeek = strchr(pParser->pLast, ' ');
  if (pSeek == NULL) {
    httpSendErrorResp(pContext, HTTP_PARSE_HTTP_METHOD_ERROR);
    return false;
  }
  pParser->method.pos = pParser->pLast;
  pParser->method.len = (int16_t)(pSeek - pParser->pLast);
  pParser->method.pos[pParser->method.len] = 0;
  pParser->pLast = pSeek + 1;

  httpTrace("context:%p, fd:%d, ip:%s, httpMethod:%s", pContext, pContext->fd, pContext->ipstr, pParser->method.pos);
  return true;
}