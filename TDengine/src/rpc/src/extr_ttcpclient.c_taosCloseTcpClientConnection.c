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
typedef  int /*<<< orphan*/  STcpFd ;

/* Variables and functions */
 int /*<<< orphan*/  taosCleanUpTcpFdObj (int /*<<< orphan*/ *) ; 

void taosCloseTcpClientConnection(void *chandle) {
  STcpFd *pFdObj = (STcpFd *)chandle;

  if (pFdObj == NULL) return;

  taosCleanUpTcpFdObj(pFdObj);
}