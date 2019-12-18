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
struct TYPE_3__ {void* insertReqNum; void* selectReqNum; int /*<<< orphan*/  httpReqNum; } ;
typedef  TYPE_1__ SCountInfo ;

/* Variables and functions */
 void* atomic_exchange_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpGetReqCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnodeInsertReqNum ; 
 int /*<<< orphan*/  vnodeSelectReqNum ; 

void dnodeCountRequest(SCountInfo *info) {
  httpGetReqCount(&info->httpReqNum);
  info->selectReqNum = atomic_exchange_32(&vnodeSelectReqNum, 0);
  info->insertReqNum = atomic_exchange_32(&vnodeInsertReqNum, 0);
}