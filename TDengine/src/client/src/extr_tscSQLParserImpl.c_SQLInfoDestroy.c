#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  keep; } ;
struct TYPE_9__ {int /*<<< orphan*/  pTagVals; } ;
struct TYPE_8__ {int /*<<< orphan*/  pTagColumns; int /*<<< orphan*/  pColumns; } ;
struct TYPE_12__ {scalar_t__ nAlloc; TYPE_3__ dbOpt; int /*<<< orphan*/  a; int /*<<< orphan*/  pAddColumns; int /*<<< orphan*/  varList; TYPE_2__ usingInfo; TYPE_1__ colInfo; int /*<<< orphan*/  pSelect; } ;
struct TYPE_11__ {scalar_t__ sqlType; TYPE_5__* pDCLInfo; TYPE_5__* pAlterInfo; TYPE_5__* pCreateTableInfo; int /*<<< orphan*/  pQueryInfo; } ;
typedef  TYPE_4__ SSqlInfo ;
typedef  TYPE_5__ SCreateTableSQL ;

/* Variables and functions */
 scalar_t__ ALTER_TABLE_DROP_COLUMN ; 
 scalar_t__ ALTER_TABLE_TAGS_ADD ; 
 scalar_t__ CREATE_DATABASE ; 
 scalar_t__ TSQL_CREATE_NORMAL_METER ; 
 scalar_t__ TSQL_CREATE_STREAM ; 
 scalar_t__ TSQL_QUERY_METER ; 
 int /*<<< orphan*/  destroyQuerySql (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tFieldListDestroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tVariantListDestroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tfree (TYPE_5__*) ; 

void SQLInfoDestroy(SSqlInfo *pInfo) {
  if (pInfo == NULL) return;

  if (pInfo->sqlType == TSQL_QUERY_METER) {
    destroyQuerySql(pInfo->pQueryInfo);
  } else if (pInfo->sqlType >= TSQL_CREATE_NORMAL_METER && pInfo->sqlType <= TSQL_CREATE_STREAM) {
    SCreateTableSQL *pCreateTableInfo = pInfo->pCreateTableInfo;
    destroyQuerySql(pCreateTableInfo->pSelect);

    tFieldListDestroy(pCreateTableInfo->colInfo.pColumns);
    tFieldListDestroy(pCreateTableInfo->colInfo.pTagColumns);

    tVariantListDestroy(pCreateTableInfo->usingInfo.pTagVals);
    tfree(pInfo->pCreateTableInfo);
  } else if (pInfo->sqlType >= ALTER_TABLE_TAGS_ADD && pInfo->sqlType <= ALTER_TABLE_DROP_COLUMN) {
    tVariantListDestroy(pInfo->pAlterInfo->varList);
    tFieldListDestroy(pInfo->pAlterInfo->pAddColumns);
    tfree(pInfo->pAlterInfo);
  } else {
    if (pInfo->pDCLInfo != NULL && pInfo->pDCLInfo->nAlloc > 0) {
      free(pInfo->pDCLInfo->a);
    }

    if (pInfo->sqlType == CREATE_DATABASE) {
      tVariantListDestroy(pInfo->pDCLInfo->dbOpt.keep);
    }

    tfree(pInfo->pDCLInfo);
  }
}