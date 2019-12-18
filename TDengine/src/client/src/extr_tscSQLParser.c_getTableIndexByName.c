#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_6__ {int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  SSqlCmd ;
typedef  TYPE_1__ SSQLToken ;
typedef  int /*<<< orphan*/  SColumnIndex ;

/* Variables and functions */
 scalar_t__ TSDB_CODE_INVALID_SQL ; 
 scalar_t__ TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  extractTableNameFromToken (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ getMeterIndex (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int32_t getTableIndexByName(SSQLToken* pToken, SSqlCmd* pCmd, SColumnIndex* pIndex) {
  SSQLToken tableToken = {0};
  extractTableNameFromToken(pToken, &tableToken);

  if (getMeterIndex(&tableToken, pCmd, pIndex) != TSDB_CODE_SUCCESS) {
    return TSDB_CODE_INVALID_SQL;
  }

  return TSDB_CODE_SUCCESS;
}