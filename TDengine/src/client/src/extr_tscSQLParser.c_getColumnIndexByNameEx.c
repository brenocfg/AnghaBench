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
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_5__ {scalar_t__ numOfTables; int /*<<< orphan*/ * pMeterInfo; } ;
typedef  TYPE_1__ SSqlCmd ;
typedef  int /*<<< orphan*/  SSQLToken ;
typedef  int /*<<< orphan*/  SColumnIndex ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_CODE_INVALID_SQL ; 
 scalar_t__ TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  doGetColumnIndexByName (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ getTableIndexByName (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

int32_t getColumnIndexByNameEx(SSQLToken* pToken, SSqlCmd* pCmd, SColumnIndex* pIndex) {
  if (pCmd->pMeterInfo == NULL || pCmd->numOfTables == 0) {
    return TSDB_CODE_INVALID_SQL;
  }

  SSQLToken tmpToken = *pToken;

  if (getTableIndexByName(&tmpToken, pCmd, pIndex) != TSDB_CODE_SUCCESS) {
    return TSDB_CODE_INVALID_SQL;
  }

  return doGetColumnIndexByName(&tmpToken, pCmd, pIndex);
}