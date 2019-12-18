#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_8__ ;
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
struct TYPE_30__ {TYPE_2__* pNode; } ;
typedef  TYPE_3__ tSQLExprItem ;
typedef  scalar_t__ int32_t ;
struct TYPE_35__ {scalar_t__ tableIndex; scalar_t__ columnIndex; scalar_t__ member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_34__ {scalar_t__ numOfColumns; } ;
struct TYPE_33__ {TYPE_7__* pMeterMeta; } ;
struct TYPE_32__ {int /*<<< orphan*/  name; int /*<<< orphan*/  bytes; int /*<<< orphan*/  type; } ;
struct TYPE_28__ {scalar_t__ numOfOutputCols; } ;
struct TYPE_31__ {scalar_t__ numOfTables; int /*<<< orphan*/  type; TYPE_1__ fieldsInfo; } ;
struct TYPE_29__ {scalar_t__ nSQLOptr; int /*<<< orphan*/  colInfo; } ;
typedef  TYPE_4__ SSqlCmd ;
typedef  TYPE_5__ SSchema ;
typedef  TYPE_6__ SMeterMetaInfo ;
typedef  TYPE_7__ SMeterMeta ;
typedef  TYPE_8__ SColumnIndex ;

/* Variables and functions */
 TYPE_8__ COLUMN_INDEX_INITIALIZER ; 
 scalar_t__ COLUMN_INDEX_INITIAL_VAL ; 
 scalar_t__ TK_ALL ; 
 scalar_t__ TK_ID ; 
 scalar_t__ TSDB_CODE_INVALID_SQL ; 
 scalar_t__ TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  TSDB_DATA_TYPE_BINARY ; 
 int /*<<< orphan*/  TSDB_FUNC_TAGPRJ ; 
 int /*<<< orphan*/  TSDB_METER_NAME_LEN ; 
 int /*<<< orphan*/  TSDB_QUERY_TYPE_STABLE_QUERY ; 
 scalar_t__ TSDB_TBNAME_COLUMN_INDEX ; 
 int /*<<< orphan*/  TSQL_TBNAME_L ; 
 scalar_t__ UTIL_METER_IS_NOMRAL_METER (TYPE_6__*) ; 
 int /*<<< orphan*/  addProjectQueryCol (TYPE_4__*,scalar_t__,TYPE_8__*,TYPE_3__*) ; 
 scalar_t__ doAddProjectionExprAndResultFields (TYPE_4__*,TYPE_8__*,scalar_t__) ; 
 scalar_t__ getColumnIndexByNameEx (int /*<<< orphan*/ *,TYPE_4__*,TYPE_8__*) ; 
 scalar_t__ getTableIndexByName (int /*<<< orphan*/ *,TYPE_4__*,TYPE_8__*) ; 
 int /*<<< orphan*/  setErrMsg (TYPE_4__*,char const*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscAddSpecialColumnForSelect (TYPE_4__*,scalar_t__,int /*<<< orphan*/ ,TYPE_8__*,TYPE_5__*,int) ; 
 TYPE_6__* tscGetMeterMetaInfo (TYPE_4__*,scalar_t__) ; 

int32_t addProjectionExprAndResultField(SSqlCmd* pCmd, tSQLExprItem* pItem) {
  const char* msg0 = "invalid column name";
  const char* msg1 = "tag for table query is not allowed";

  int32_t startPos = pCmd->fieldsInfo.numOfOutputCols;

  if (pItem->pNode->nSQLOptr == TK_ALL) {  // project on all fields
    SColumnIndex index = COLUMN_INDEX_INITIALIZER;
    if (getTableIndexByName(&pItem->pNode->colInfo, pCmd, &index) != TSDB_CODE_SUCCESS) {
      return TSDB_CODE_INVALID_SQL;
    }

    // all meters columns are required
    if (index.tableIndex == COLUMN_INDEX_INITIAL_VAL) {  // all table columns are required.
      for (int32_t i = 0; i < pCmd->numOfTables; ++i) {
        index.tableIndex = i;
        int32_t inc = doAddProjectionExprAndResultFields(pCmd, &index, startPos);
        startPos += inc;
      }
    } else {
      doAddProjectionExprAndResultFields(pCmd, &index, startPos);
    }
  } else if (pItem->pNode->nSQLOptr == TK_ID) {  // simple column projection query
    SColumnIndex index = COLUMN_INDEX_INITIALIZER;

    if (getColumnIndexByNameEx(&pItem->pNode->colInfo, pCmd, &index) != TSDB_CODE_SUCCESS) {
      setErrMsg(pCmd, msg0);
      return TSDB_CODE_INVALID_SQL;
    }

    if (index.columnIndex == TSDB_TBNAME_COLUMN_INDEX) {
      SColumnIndex index1 = {0, TSDB_TBNAME_COLUMN_INDEX};
      SSchema      colSchema = {.type = TSDB_DATA_TYPE_BINARY, .bytes = TSDB_METER_NAME_LEN};
      strcpy(colSchema.name, TSQL_TBNAME_L);

      pCmd->type = TSDB_QUERY_TYPE_STABLE_QUERY;
      tscAddSpecialColumnForSelect(pCmd, startPos, TSDB_FUNC_TAGPRJ, &index1, &colSchema, true);
    } else {
      SMeterMetaInfo* pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, index.tableIndex);
      SMeterMeta*     pMeterMeta = pMeterMetaInfo->pMeterMeta;

      if (index.columnIndex >= pMeterMeta->numOfColumns && UTIL_METER_IS_NOMRAL_METER(pMeterMetaInfo)) {
        setErrMsg(pCmd, msg1);
        return TSDB_CODE_INVALID_SQL;
      }

      addProjectQueryCol(pCmd, startPos, &index, pItem);
    }
  } else {
    return TSDB_CODE_INVALID_SQL;
  }

  return TSDB_CODE_SUCCESS;
}