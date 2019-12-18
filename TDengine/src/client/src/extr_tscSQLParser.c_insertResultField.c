#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int8_t ;
typedef  size_t int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_7__ {size_t num; int /*<<< orphan*/ * ids; } ;
struct TYPE_6__ {int /*<<< orphan*/  fieldsInfo; } ;
typedef  TYPE_1__ SSqlCmd ;
typedef  TYPE_2__ SColumnList ;

/* Variables and functions */
 size_t TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  tscColumnBaseInfoInsert (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tscFieldInfoSetValue (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int32_t insertResultField(SSqlCmd* pCmd, int32_t outputIndex, SColumnList* pIdList, int16_t bytes, int8_t type,
                          char* fieldName) {
  for (int32_t i = 0; i < pIdList->num; ++i) {
    tscColumnBaseInfoInsert(pCmd, &(pIdList->ids[i]));
  }

  tscFieldInfoSetValue(&pCmd->fieldsInfo, outputIndex, type, fieldName, bytes);
  return TSDB_CODE_SUCCESS;
}