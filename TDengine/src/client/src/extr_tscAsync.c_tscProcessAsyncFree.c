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
struct TYPE_3__ {scalar_t__ ahandle; } ;
typedef  int /*<<< orphan*/  SSqlObj ;
typedef  TYPE_1__ SSchedMsg ;

/* Variables and functions */
 int /*<<< orphan*/  taos_free_result (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tscTrace (char*,int /*<<< orphan*/ *) ; 

void tscProcessAsyncFree(SSchedMsg *pMsg) {
  SSqlObj *pSql = (SSqlObj *)pMsg->ahandle;
  tscTrace("%p sql is freed", pSql);
  taos_free_result(pSql);
}