#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_9__ {int /*<<< orphan*/  payloadLen; int /*<<< orphan*/  payload; } ;
struct TYPE_8__ {TYPE_2__* pSql; } ;
struct TYPE_6__ {int /*<<< orphan*/  code; } ;
struct TYPE_7__ {TYPE_1__ res; TYPE_4__ cmd; } ;
typedef  TYPE_3__ STscObj ;
typedef  TYPE_4__ SSqlCmd ;

/* Variables and functions */
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setErrorInfo(STscObj* pObj, int32_t code, char* info) {
  if (pObj == NULL) {
    return;
  }

  SSqlCmd* pCmd = &pObj->pSql->cmd;

  pObj->pSql->res.code = code;
  strncpy(pCmd->payload, info, pCmd->payloadLen);
}