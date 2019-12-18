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
typedef  scalar_t__ int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  requestNum; } ;

/* Variables and functions */
 scalar_t__ atomic_exchange_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* httpServer ; 

void httpGetReqCount(int32_t *httpReqestNum) {
  if (httpServer != NULL) {
    *httpReqestNum = atomic_exchange_32(&httpServer->requestNum, 0);
  } else {
    *httpReqestNum = 0;
  }
}