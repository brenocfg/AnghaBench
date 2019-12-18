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
typedef  int /*<<< orphan*/  probes ;
typedef  int /*<<< orphan*/  nodelay ;
typedef  int /*<<< orphan*/  interval ;
typedef  int /*<<< orphan*/  alivetime ;
typedef  int /*<<< orphan*/  alive ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SOL_TCP ; 
 int /*<<< orphan*/  SO_KEEPALIVE ; 
 int /*<<< orphan*/  TCP_KEEPCNT ; 
 int /*<<< orphan*/  TCP_KEEPIDLE ; 
 int /*<<< orphan*/  TCP_KEEPINTVL ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  pError (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ taosSetSockOpt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 

int taosKeepTcpAlive(int sockFd) {
  int alive = 1;
  if (taosSetSockOpt(sockFd, SOL_SOCKET, SO_KEEPALIVE, (void *)&alive, sizeof(alive)) < 0) {
    pError("fd:%d setsockopt SO_KEEPALIVE failed: %d (%s)", sockFd, errno, strerror(errno));
    close(sockFd);
    return -1;
  }

  int probes = 3;
  if (taosSetSockOpt(sockFd, SOL_TCP, TCP_KEEPCNT, (void *)&probes, sizeof(probes)) < 0) {
    pError("fd:%d setsockopt SO_KEEPCNT failed: %d (%s)", sockFd, errno, strerror(errno));
    close(sockFd);
    return -1;
  }

  int alivetime = 10;
  if (taosSetSockOpt(sockFd, SOL_TCP, TCP_KEEPIDLE, (void *)&alivetime, sizeof(alivetime)) < 0) {
    pError("fd:%d setsockopt SO_KEEPIDLE failed: %d (%s)", sockFd, errno, strerror(errno));
    close(sockFd);
    return -1;
  }

  int interval = 3;
  if (taosSetSockOpt(sockFd, SOL_TCP, TCP_KEEPINTVL, (void *)&interval, sizeof(interval)) < 0) {
    pError("fd:%d setsockopt SO_KEEPINTVL failed: %d (%s)", sockFd, errno, strerror(errno));
    close(sockFd);
    return -1;
  }

  int nodelay = 1;
  if (taosSetSockOpt(sockFd, IPPROTO_TCP, TCP_NODELAY, (void *)&nodelay, sizeof(nodelay)) < 0) {
    pError("fd:%d setsockopt TCP_NODELAY failed %d (%s)", sockFd, errno, strerror(errno));
    close(sockFd);
    return -1;
  }

  return 0;
}