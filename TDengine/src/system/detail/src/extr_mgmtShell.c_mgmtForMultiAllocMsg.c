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
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_3__ {int /*<<< orphan*/  thandle; } ;
typedef  int /*<<< orphan*/  STaosRsp ;
typedef  TYPE_1__ SConnObj ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_MSG_TYPE_MULTI_METERINFO_RSP ; 
 char* taosBuildRspMsgWithSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *mgmtForMultiAllocMsg(SConnObj *pConn, int32_t size, char **pMsg, STaosRsp **pRsp) {
  char *pStart = taosBuildRspMsgWithSize(pConn->thandle, TSDB_MSG_TYPE_MULTI_METERINFO_RSP, size);
  if (pStart == NULL) return 0;
  *pMsg = pStart;
  *pRsp = (STaosRsp *)(*pMsg);

  return pStart;
}