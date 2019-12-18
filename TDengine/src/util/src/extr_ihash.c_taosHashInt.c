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
typedef  int uint64_t ;
typedef  int int32_t ;
struct TYPE_2__ {int maxSessions; } ;
typedef  TYPE_1__ IHashObj ;

/* Variables and functions */

int32_t taosHashInt(void *handle, uint64_t key) {
  IHashObj *pObj = (IHashObj *)handle;
  int32_t   hash = key % pObj->maxSessions;
  return hash;
}