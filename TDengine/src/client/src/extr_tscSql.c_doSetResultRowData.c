#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_12__ {int numOfOutputCols; } ;
struct TYPE_16__ {scalar_t__ nAggTimeInterval; TYPE_1__ fieldsInfo; int /*<<< orphan*/  order; } ;
struct TYPE_14__ {void** tsrow; int* bytes; int row; void** buffer; } ;
struct TYPE_15__ {TYPE_3__ res; TYPE_5__ cmd; } ;
struct TYPE_13__ {scalar_t__ type; scalar_t__ bytes; } ;
typedef  TYPE_2__ TAOS_FIELD ;
typedef  TYPE_3__ SSqlRes ;
typedef  TYPE_4__ SSqlObj ;
typedef  TYPE_5__ SSqlCmd ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_UNICODE_ENCODEC ; 
 void* TSC_GET_RESPTR_BASE (TYPE_3__*,TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ TSDB_DATA_TYPE_NCHAR ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ isNull (void*,scalar_t__) ; 
 void* malloc (scalar_t__) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 void* realloc (void*,scalar_t__) ; 
 scalar_t__ taosUcs4ToMbs (void*,scalar_t__,void*) ; 
 int /*<<< orphan*/  tsCharset ; 
 int /*<<< orphan*/  tscError (char*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 TYPE_2__* tscFieldInfoGetField (TYPE_5__*,int) ; 

__attribute__((used)) static void **doSetResultRowData(SSqlObj *pSql) {
  SSqlCmd *pCmd = &pSql->cmd;
  SSqlRes *pRes = &pSql->res;

  int32_t num = 0;

  for (int i = 0; i < pCmd->fieldsInfo.numOfOutputCols; ++i) {
    pRes->tsrow[i] = TSC_GET_RESPTR_BASE(pRes, pCmd, i, pCmd->order) + pRes->bytes[i] * pRes->row;

    // primary key column cannot be null in interval query, no need to check
    if (i == 0 && pCmd->nAggTimeInterval > 0) {
      continue;
    }

    TAOS_FIELD *pField = tscFieldInfoGetField(pCmd, i);

    if (isNull(pRes->tsrow[i], pField->type)) {
      pRes->tsrow[i] = NULL;
    } else if (pField->type == TSDB_DATA_TYPE_NCHAR) {
      // convert unicode to native code in a temporary buffer extra one byte for terminated symbol
      if (pRes->buffer[num] == NULL) {
        pRes->buffer[num] = malloc(pField->bytes + 1);
      } else {
        pRes->buffer[num] = realloc(pRes->buffer[num], pField->bytes + 1);
      }

      /* string terminated */
      memset(pRes->buffer[num], 0, pField->bytes + 1);

      if (taosUcs4ToMbs(pRes->tsrow[i], pField->bytes, pRes->buffer[num])) {
        pRes->tsrow[i] = pRes->buffer[num];
      } else {
        tscError("%p charset:%s to %s. val:%ls convert failed.", pSql, DEFAULT_UNICODE_ENCODEC, tsCharset, pRes->tsrow);
        pRes->tsrow[i] = NULL;
      }
      num++;
    }
  }

  assert(num <= pCmd->fieldsInfo.numOfOutputCols);

  return pRes->tsrow;
}