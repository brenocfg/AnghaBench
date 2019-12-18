#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ SFdObj ;

/* Variables and functions */
 scalar_t__ send (int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ) ; 

int taosSendTcpServerData(uint32_t ip, short port, char *data, int len, void *chandle) {
  SFdObj *pFdObj = (SFdObj *)chandle;

  if (chandle == NULL) return -1;

  return (int)send(pFdObj->fd, data, (size_t)len, 0);
}