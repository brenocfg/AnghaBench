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

uint32_t taosHashString(void *handle, char *string) {
  SHashObj *pObj = (SHashObj *)handle;
  uint32_t  hash = 0, hashv;
  char *    c;

  c = string;
  while (*c) {
    hash += *((int *)c);
    c += 4;
  }

  hashv = hash / pObj->maxSessions;
  hash = (hashv + hash % pObj->maxSessions) % pObj->maxSessions;

  return hash;
}