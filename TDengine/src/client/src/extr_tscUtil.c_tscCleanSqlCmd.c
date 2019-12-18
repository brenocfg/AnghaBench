#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {char* payload; int /*<<< orphan*/  allocSize; int /*<<< orphan*/ * pMeterInfo; } ;
typedef  TYPE_1__ SSqlCmd ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tscFreeSqlCmdData (TYPE_1__*) ; 

void tscCleanSqlCmd(SSqlCmd* pCmd) {
  tscFreeSqlCmdData(pCmd);

  assert(pCmd->pMeterInfo == NULL);

  uint32_t allocSize = pCmd->allocSize;
  char*    allocPtr = pCmd->payload;

  memset(pCmd, 0, sizeof(SSqlCmd));

  // restore values
  pCmd->allocSize = allocSize;
  pCmd->payload = allocPtr;
}