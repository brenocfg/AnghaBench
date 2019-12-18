#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  label; } ;
struct TYPE_10__ {int bufsize; scalar_t__* buffer; } ;
struct TYPE_11__ {TYPE_5__* pThread; int /*<<< orphan*/  ipstr; int /*<<< orphan*/  fd; TYPE_1__ parser; } ;
typedef  TYPE_1__ HttpParser ;
typedef  TYPE_2__ HttpContext ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ EWOULDBLOCK ; 
 int HTTP_BUFFER_SIZE ; 
 int /*<<< orphan*/  HTTP_REQUSET_TOO_BIG ; 
 int HTTP_STEP_SIZE ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  httpError (char*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,...) ; 
 int /*<<< orphan*/  httpReadDirtyData (TYPE_2__*) ; 
 int /*<<< orphan*/  httpRemoveContextFromEpoll (TYPE_5__*,TYPE_2__*) ; 
 int /*<<< orphan*/  httpSendErrorResp (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpTrace (char*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,...) ; 
 scalar_t__ taosReadSocket (int /*<<< orphan*/ ,scalar_t__*,int) ; 

bool httpReadDataImp(HttpContext *pContext) {
  HttpParser *pParser = &pContext->parser;

  while (pParser->bufsize <= (HTTP_BUFFER_SIZE - HTTP_STEP_SIZE)) {
    int nread = (int)taosReadSocket(pContext->fd, pParser->buffer + pParser->bufsize, HTTP_STEP_SIZE);
    if (nread >= 0 && nread < HTTP_STEP_SIZE) {
      pParser->bufsize += nread;
      break;
    } else if (nread < 0) {
      if (errno == EINTR || errno == EAGAIN || errno == EWOULDBLOCK) {
        httpTrace("context:%p, fd:%d, ip:%s, read from socket error:%d, wait another event",
                  pContext, pContext->fd, pContext->ipstr, errno);
        break;
      } else {
        httpError("context:%p, fd:%d, ip:%s, read from socket error:%d, close connect",
                  pContext, pContext->fd, pContext->ipstr, errno);
        return false;
      }
    } else {
      pParser->bufsize += nread;
    }

    if (pParser->bufsize >= (HTTP_BUFFER_SIZE - HTTP_STEP_SIZE)) {
      httpReadDirtyData(pContext);
      httpError("context:%p, fd:%d, ip:%s, thread:%s, request big than:%d",
                pContext, pContext->fd, pContext->ipstr, pContext->pThread->label, HTTP_BUFFER_SIZE);
      httpRemoveContextFromEpoll(pContext->pThread, pContext);
      httpSendErrorResp(pContext, HTTP_REQUSET_TOO_BIG);
      return false;
    }
  }

  pParser->buffer[pParser->bufsize] = 0;
  httpTrace("context:%p, fd:%d, ip:%s, thread:%s, read size:%d",
            pContext, pContext->fd, pContext->ipstr, pContext->pThread->label, pParser->bufsize);

  return true;
}