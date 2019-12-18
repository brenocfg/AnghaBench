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
struct linger {int l_onoff; scalar_t__ l_linger; } ;
typedef  int /*<<< orphan*/  linger ;

/* Variables and functions */
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_LINGER ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  pError (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosCloseSocket (int) ; 
 scalar_t__ taosSetSockOpt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 

void taosCloseTcpSocket(int sockFd) {
  struct linger linger;
  linger.l_onoff = 1;
  linger.l_linger = 0;
  if (taosSetSockOpt(sockFd, SOL_SOCKET, SO_LINGER, (void *)&linger, sizeof(linger)) < 0) {
    pError("setsockopt SO_LINGER failed: %d (%s)", errno, strerror(errno));
  }

  taosCloseSocket(sockFd);
}