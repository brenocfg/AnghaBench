#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct HttpContext {int fd; int /*<<< orphan*/  ipstr; } ;

/* Variables and functions */
 int HTTP_WRITE_RETRY_TIMES ; 
 int /*<<< orphan*/  HTTP_WRITE_WAIT_TIME_MS ; 
 int /*<<< orphan*/  MSG_NOSIGNAL ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  httpTrace (char*,struct HttpContext*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ send (int,char const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosMsleep (int /*<<< orphan*/ ) ; 

int httpWriteBufByFd(struct HttpContext* pContext, const char* buf, int sz) {
  int       len;
  int       countWait = 0;
  int       writeLen = 0;

  do {
    if (pContext->fd > 2){
      len = (int)send(pContext->fd, buf + writeLen, (size_t)(sz - writeLen), MSG_NOSIGNAL);
    }
    else {
      return sz;
    }

    if (len < 0) {
      httpTrace("context:%p, fd:%d, ip:%s, socket write errno:%d, times:%d",
                pContext, pContext->fd, pContext->ipstr, errno, countWait);
      if (++countWait > HTTP_WRITE_RETRY_TIMES) break;
      taosMsleep(HTTP_WRITE_WAIT_TIME_MS);
      continue;
    } else if (len == 0) {
      httpTrace("context:%p, fd:%d, ip:%s, socket write errno:%d, connect already closed",
                pContext, pContext->fd, pContext->ipstr, errno);
      break;
    } else {
      countWait = 0;
      writeLen += len;
    }
  } while (writeLen < sz);

  return writeLen;
}