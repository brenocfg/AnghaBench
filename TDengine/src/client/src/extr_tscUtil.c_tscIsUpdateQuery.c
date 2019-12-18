#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ command; } ;
struct TYPE_6__ {TYPE_1__* pSql; struct TYPE_6__* signature; } ;
struct TYPE_5__ {TYPE_3__ cmd; } ;
typedef  TYPE_2__ STscObj ;
typedef  TYPE_3__ SSqlCmd ;

/* Variables and functions */
 int TSDB_CODE_DISCONNECTED ; 
 scalar_t__ TSDB_SQL_DROP_DNODE ; 
 scalar_t__ TSDB_SQL_INSERT ; 
 scalar_t__ TSDB_SQL_USE_DB ; 
 int globalCode ; 

bool tscIsUpdateQuery(STscObj* pObj) {
  if (pObj == NULL || pObj->signature != pObj) {
    globalCode = TSDB_CODE_DISCONNECTED;
    return TSDB_CODE_DISCONNECTED;
  }

  SSqlCmd* pCmd = &pObj->pSql->cmd;
  return ((pCmd->command >= TSDB_SQL_INSERT && pCmd->command <= TSDB_SQL_DROP_DNODE) ||
      TSDB_SQL_USE_DB == pCmd->command) ? 1 : 0;

}