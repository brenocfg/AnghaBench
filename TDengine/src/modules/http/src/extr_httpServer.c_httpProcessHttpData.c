#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_4__* ptr; } ;
struct epoll_event {int events; TYPE_1__ data; } ;
typedef  int /*<<< orphan*/  sigset_t ;
struct TYPE_19__ {scalar_t__ fd; int /*<<< orphan*/  accessTimes; int /*<<< orphan*/  state; int /*<<< orphan*/  ipstr; TYPE_3__* pThread; struct TYPE_19__* signature; } ;
struct TYPE_18__ {int numOfFds; TYPE_2__* pServer; int /*<<< orphan*/  (* processData ) (TYPE_4__*) ;int /*<<< orphan*/  pollFd; int /*<<< orphan*/  threadMutex; int /*<<< orphan*/  fdReady; } ;
struct TYPE_17__ {int /*<<< orphan*/  requestNum; int /*<<< orphan*/  online; } ;
typedef  TYPE_3__ HttpThread ;
typedef  TYPE_4__ HttpContext ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLHUP ; 
 int EPOLLPRI ; 
 int EPOLLRDHUP ; 
 int /*<<< orphan*/  HTTP_CONTEXT_STATE_READY ; 
 int HTTP_MAX_EVENTS ; 
 int /*<<< orphan*/  HTTP_SERVER_OFFLINE ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  atomic_fetch_add_32 (int /*<<< orphan*/ *,int) ; 
 int epoll_wait (int /*<<< orphan*/ ,struct epoll_event*,int,int) ; 
 int /*<<< orphan*/  httpAlterContextState (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpCloseContextByServer (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  httpContextStateStr (int /*<<< orphan*/ ) ; 
 scalar_t__ httpReadData (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  httpReadDirtyData (TYPE_4__*) ; 
 int /*<<< orphan*/  httpRemoveContextFromEpoll (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  httpSendErrorResp (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpTrace (char*,TYPE_4__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_sigmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 

void httpProcessHttpData(void *param) {
  HttpThread  *pThread = (HttpThread *)param;
  HttpContext *pContext;
  int          fdNum;

  sigset_t set;
  sigemptyset(&set);
  sigaddset(&set, SIGPIPE);
  pthread_sigmask(SIG_SETMASK, &set, NULL);

  while (1) {
    pthread_mutex_lock(&pThread->threadMutex);
    if (pThread->numOfFds < 1) {
      pthread_cond_wait(&pThread->fdReady, &pThread->threadMutex);
    }
    pthread_mutex_unlock(&pThread->threadMutex);

    struct epoll_event events[HTTP_MAX_EVENTS];
    //-1 means uncertainty, 0-nowait, 1-wait 1 ms, set it from -1 to 1
    fdNum = epoll_wait(pThread->pollFd, events, HTTP_MAX_EVENTS, 1);
    if (fdNum <= 0) continue;

    for (int i = 0; i < fdNum; ++i) {
      pContext = events[i].data.ptr;
      if (pContext->signature != pContext || pContext->pThread != pThread || pContext->fd <= 0) {
        continue;
      }

      if (events[i].events & EPOLLPRI) {
        httpTrace("context:%p, fd:%d, ip:%s, state:%s, EPOLLPRI events occured, accessed:%d, close connect",
                  pContext, pContext->fd, pContext->ipstr, httpContextStateStr(pContext->state), pContext->accessTimes);
        httpRemoveContextFromEpoll(pThread, pContext);
        httpCloseContextByServer(pThread, pContext);
        continue;
      }

      if (events[i].events & EPOLLRDHUP) {
        httpTrace("context:%p, fd:%d, ip:%s, state:%s, EPOLLRDHUP events occured, accessed:%d, close connect",
                  pContext, pContext->fd, pContext->ipstr, httpContextStateStr(pContext->state), pContext->accessTimes);
        httpRemoveContextFromEpoll(pThread, pContext);
        httpCloseContextByServer(pThread, pContext);
        continue;
      }

      if (events[i].events & EPOLLERR) {
        httpTrace("context:%p, fd:%d, ip:%s, state:%s, EPOLLERR events occured, accessed:%d, close connect",
                  pContext, pContext->fd, pContext->ipstr, httpContextStateStr(pContext->state), pContext->accessTimes);
        httpRemoveContextFromEpoll(pThread, pContext);
        httpCloseContextByServer(pThread, pContext);
        continue;
      }

      if (events[i].events & EPOLLHUP) {
        httpTrace("context:%p, fd:%d, ip:%s, state:%s, EPOLLHUP events occured, accessed:%d, close connect",
                  pContext, pContext->fd, pContext->ipstr, httpContextStateStr(pContext->state), pContext->accessTimes);
        httpRemoveContextFromEpoll(pThread, pContext);
        httpCloseContextByServer(pThread, pContext);
        continue;
      }

      if (!httpAlterContextState(pContext, HTTP_CONTEXT_STATE_READY, HTTP_CONTEXT_STATE_READY)) {
        httpTrace("context:%p, fd:%d, ip:%s, state:%s, not in ready state, ignore read events",
                pContext, pContext->fd, pContext->ipstr, httpContextStateStr(pContext->state));
        continue;
      }

      if (!pContext->pThread->pServer->online) {
        httpTrace("context:%p, fd:%d, ip:%s, state:%s, server is not online, accessed:%d, close connect",
                  pContext, pContext->fd, pContext->ipstr, httpContextStateStr(pContext->state), pContext->accessTimes);
        httpRemoveContextFromEpoll(pThread, pContext);
        httpReadDirtyData(pContext);
        httpSendErrorResp(pContext, HTTP_SERVER_OFFLINE);
        httpCloseContextByServer(pThread, pContext);
        continue;
      } else {
        if (httpReadData(pThread, pContext)) {
          (*(pThread->processData))(pContext);
          atomic_fetch_add_32(&pThread->pServer->requestNum, 1);
        }
      }
    }
  }
}