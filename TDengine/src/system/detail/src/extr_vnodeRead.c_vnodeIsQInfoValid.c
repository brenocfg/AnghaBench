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
typedef  scalar_t__ uint64_t ;
struct TYPE_2__ {scalar_t__ signature; } ;
typedef  TYPE_1__ SQInfo ;

/* Variables and functions */
 scalar_t__ TSDB_QINFO_QUERY_FLAG ; 

bool vnodeIsQInfoValid(void *param) {
  SQInfo *pQInfo = (SQInfo *)param;
  if (pQInfo == NULL) {
    return false;
  }

  /*
   * pQInfo->signature may be changed by another thread, so we assign value of signature
   * into local variable, then compare by using local variable
   */
  uint64_t sig = pQInfo->signature;
  return (sig == (uint64_t)pQInfo) || (sig == TSDB_QINFO_QUERY_FLAG);
}