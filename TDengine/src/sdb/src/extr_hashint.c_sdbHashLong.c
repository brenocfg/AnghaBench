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
typedef  int uint32_t ;
struct TYPE_2__ {int maxSessions; } ;
typedef  TYPE_1__ SHashObj ;

/* Variables and functions */

int sdbHashLong(void *handle, uint32_t ip) {
  SHashObj *pObj = (SHashObj *)handle;
  int       hash = 0;

  hash = ip >> 16;
  hash += (ip & 0xFFFF);

  hash = hash % pObj->maxSessions;

  return hash;
}