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
struct TYPE_3__ {int /*<<< orphan*/  thandle; } ;
typedef  TYPE_1__ SConnObj ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_CODE_OPS_NOT_SUPPORT ; 
 int /*<<< orphan*/  TSDB_MSG_TYPE_CREATE_PNODE_RSP ; 
 int taosSendSimpleRsp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mgmtProcessCreateDnodeMsg(char *pMsg, int msgLen, SConnObj *pConn) {
  return taosSendSimpleRsp(pConn->thandle, TSDB_MSG_TYPE_CREATE_PNODE_RSP, TSDB_CODE_OPS_NOT_SUPPORT);
}