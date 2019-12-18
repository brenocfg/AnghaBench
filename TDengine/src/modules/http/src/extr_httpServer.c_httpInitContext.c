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
struct TYPE_8__ {int /*<<< orphan*/  buffer; int /*<<< orphan*/  pLast; int /*<<< orphan*/  pCur; } ;
struct TYPE_9__ {int /*<<< orphan*/  parsed; int /*<<< orphan*/  accessTimes; TYPE_1__* pThread; int /*<<< orphan*/  ipstr; int /*<<< orphan*/  fd; TYPE_2__ parser; TYPE_2__ singleCmd; int /*<<< orphan*/ * timer; int /*<<< orphan*/ * encodeMethod; int /*<<< orphan*/  reqType; void* contentEncoding; void* acceptEncoding; int /*<<< orphan*/  httpChunked; int /*<<< orphan*/  httpKeepAlive; int /*<<< orphan*/  httpVersion; int /*<<< orphan*/  lastAccessTime; } ;
struct TYPE_7__ {int /*<<< orphan*/  label; } ;
typedef  int /*<<< orphan*/  HttpSqlCmd ;
typedef  TYPE_2__ HttpParser ;
typedef  TYPE_3__ HttpContext ;

/* Variables and functions */
 void* HTTP_COMPRESS_IDENTITY ; 
 int /*<<< orphan*/  HTTP_KEEPALIVE_NO_INPUT ; 
 int /*<<< orphan*/  HTTP_REQTYPE_OTHERS ; 
 int /*<<< orphan*/  HTTP_UNCUNKED ; 
 int /*<<< orphan*/  HTTP_VERSION_10 ; 
 int /*<<< orphan*/  httpTrace (char*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  taosGetTimestampSec () ; 

bool httpInitContext(HttpContext *pContext) {
  pContext->accessTimes++;
  pContext->lastAccessTime = taosGetTimestampSec();
  pContext->httpVersion = HTTP_VERSION_10;
  pContext->httpKeepAlive = HTTP_KEEPALIVE_NO_INPUT;
  pContext->httpChunked = HTTP_UNCUNKED;
  pContext->acceptEncoding = HTTP_COMPRESS_IDENTITY;
  pContext->contentEncoding = HTTP_COMPRESS_IDENTITY;
  pContext->reqType = HTTP_REQTYPE_OTHERS;
  pContext->encodeMethod = NULL;
  pContext->timer = NULL;
  memset(&pContext->singleCmd, 0, sizeof(HttpSqlCmd));

  HttpParser *pParser = &pContext->parser;
  memset(pParser, 0, sizeof(HttpParser));
  pParser->pCur = pParser->pLast = pParser->buffer;

  httpTrace("context:%p, fd:%d, ip:%s, thread:%s, accessTimes:%d, parsed:%d",
          pContext, pContext->fd, pContext->ipstr, pContext->pThread->label, pContext->accessTimes, pContext->parsed);
  return true;
}