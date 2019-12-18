#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_17__ {scalar_t__ n; int /*<<< orphan*/  z; } ;
struct TYPE_19__ {TYPE_5__ precision; TYPE_3__* keep; } ;
struct TYPE_18__ {int /*<<< orphan*/  precision; void* daysToKeep2; void* daysToKeep1; void* daysToKeep; } ;
struct TYPE_16__ {scalar_t__ payload; } ;
struct TYPE_15__ {int nExpr; TYPE_2__* a; } ;
struct TYPE_13__ {int /*<<< orphan*/  i64Key; } ;
struct TYPE_14__ {TYPE_1__ pVar; } ;
typedef  TYPE_4__ SSqlCmd ;
typedef  TYPE_5__ SSQLToken ;
typedef  int /*<<< orphan*/  SMgmtHead ;
typedef  TYPE_6__ SCreateDbMsg ;
typedef  TYPE_7__ SCreateDBInfo ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_CODE_INVALID_SQL ; 
 int /*<<< orphan*/  TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  TSDB_TIME_PRECISION_MICRO ; 
 int /*<<< orphan*/  TSDB_TIME_PRECISION_MICRO_STR ; 
 int /*<<< orphan*/  TSDB_TIME_PRECISION_MILLI ; 
 int /*<<< orphan*/  TSDB_TIME_PRECISION_MILLI_STR ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setCreateDBOption (TYPE_6__*,TYPE_7__*) ; 
 int /*<<< orphan*/  setErrMsg (TYPE_4__*,char const*) ; 
 scalar_t__ strdequote (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ tsRpcHeadSize ; 

int32_t parseCreateDBOptions(SCreateDBInfo* pCreateDbSql, SSqlCmd* pCmd) {
  const char* msg0 = "invalid number of options";
  const char* msg1 = "invalid time precision";

  SCreateDbMsg* pMsg = (SCreateDbMsg*)(pCmd->payload + tsRpcHeadSize + sizeof(SMgmtHead));
  setCreateDBOption(pMsg, pCreateDbSql);

  if (pCreateDbSql->keep != NULL) {
    switch (pCreateDbSql->keep->nExpr) {
      case 1:
        pMsg->daysToKeep = htonl(pCreateDbSql->keep->a[0].pVar.i64Key);
        break;
      case 2: {
        pMsg->daysToKeep = htonl(pCreateDbSql->keep->a[0].pVar.i64Key);
        pMsg->daysToKeep1 = htonl(pCreateDbSql->keep->a[1].pVar.i64Key);
        break;
      }
      case 3: {
        pMsg->daysToKeep = htonl(pCreateDbSql->keep->a[0].pVar.i64Key);
        pMsg->daysToKeep1 = htonl(pCreateDbSql->keep->a[1].pVar.i64Key);
        pMsg->daysToKeep2 = htonl(pCreateDbSql->keep->a[2].pVar.i64Key);
        break;
      }
      default: {
        setErrMsg(pCmd, msg0);
        return TSDB_CODE_INVALID_SQL;
      }
    }
  }

  SSQLToken* pToken = &pCreateDbSql->precision;
  if (pToken->n > 0) {
    pToken->n = strdequote(pToken->z);

    if (strncmp(pToken->z, TSDB_TIME_PRECISION_MILLI_STR, pToken->n) == 0 &&
        strlen(TSDB_TIME_PRECISION_MILLI_STR) == pToken->n) {
      // time precision for this db: million second
      pMsg->precision = TSDB_TIME_PRECISION_MILLI;
    } else if (strncmp(pToken->z, TSDB_TIME_PRECISION_MICRO_STR, pToken->n) == 0 &&
               strlen(TSDB_TIME_PRECISION_MICRO_STR) == pToken->n) {
      pMsg->precision = TSDB_TIME_PRECISION_MICRO;
    } else {
      setErrMsg(pCmd, msg1);
      return TSDB_CODE_INVALID_SQL;
    }
  }

  return TSDB_CODE_SUCCESS;
}