#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_4__ {scalar_t__ len; scalar_t__ rawBuf; } ;
struct TYPE_5__ {int tsOrder; TYPE_1__ tsData; } ;
typedef  scalar_t__ TSKEY ;
typedef  TYPE_1__ STSList ;
typedef  TYPE_2__ STSBuf ;

/* Variables and functions */
 scalar_t__ TSDB_CODE_SUCCESS ; 
 scalar_t__ TSDB_KEYSIZE ; 
 void* TSQL_SO_ASC ; 
 void* TSQL_SO_DESC ; 

__attribute__((used)) static int32_t setCheckTSOrder(STSBuf* pTSBuf, const char* pData, int32_t len) {
  STSList* ptsData = &pTSBuf->tsData;

  if (pTSBuf->tsOrder == -1) {
    if (ptsData->len > 0) {
      TSKEY lastKey = *(TSKEY*)(ptsData->rawBuf + ptsData->len - TSDB_KEYSIZE);

      if (lastKey > *(TSKEY*)pData) {
        pTSBuf->tsOrder = TSQL_SO_DESC;
      } else {
        pTSBuf->tsOrder = TSQL_SO_ASC;
      }
    } else if (len > TSDB_KEYSIZE) {
      // no data in current vnode, more than one ts is added, check the orders
      TSKEY k1 = *(TSKEY*)(pData);
      TSKEY k2 = *(TSKEY*)(pData + TSDB_KEYSIZE);

      if (k1 < k2) {
        pTSBuf->tsOrder = TSQL_SO_ASC;
      } else if (k1 > k2) {
        pTSBuf->tsOrder = TSQL_SO_DESC;
      } else {
        // todo handle error
      }
    }
  } else {
    // todo the timestamp order is set, check the asc/desc order of appended data
  }

  return TSDB_CODE_SUCCESS;
}