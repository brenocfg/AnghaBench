#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int initialized; int complete; int hasResult; scalar_t__ bufLen; int /*<<< orphan*/  interResultBuf; scalar_t__ numOfRes; } ;
typedef  TYPE_1__ SResultInfo ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

void initResultInfo(SResultInfo *pResInfo) {
  pResInfo->initialized = true;  // the this struct has been initialized flag

  pResInfo->complete = false;
  pResInfo->hasResult = false;
  pResInfo->numOfRes = 0;

  memset(pResInfo->interResultBuf, 0, (size_t)pResInfo->bufLen);
}