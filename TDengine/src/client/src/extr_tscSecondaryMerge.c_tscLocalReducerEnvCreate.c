#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_9__ ;
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_10__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  tOrderDescriptor ;
struct TYPE_29__ {int /*<<< orphan*/  flushModel; } ;
typedef  TYPE_3__ tExtMemBuffer ;
typedef  int /*<<< orphan*/  tColModel ;
typedef  size_t int32_t ;
struct TYPE_35__ {int /*<<< orphan*/  name; scalar_t__ bytes; int /*<<< orphan*/  type; } ;
struct TYPE_28__ {int numOfOutputCols; } ;
struct TYPE_34__ {TYPE_2__ fieldsInfo; } ;
struct TYPE_33__ {scalar_t__ resBytes; int /*<<< orphan*/  resType; } ;
struct TYPE_31__ {size_t code; } ;
struct TYPE_32__ {TYPE_5__ res; TYPE_8__ cmd; } ;
struct TYPE_30__ {int /*<<< orphan*/  name; scalar_t__ bytes; int /*<<< orphan*/  type; } ;
struct TYPE_27__ {int numOfVnodes; } ;
struct TYPE_26__ {TYPE_1__* pMetricMeta; } ;
typedef  TYPE_4__ TAOS_FIELD ;
typedef  TYPE_5__ SSqlRes ;
typedef  TYPE_6__ SSqlObj ;
typedef  TYPE_7__ SSqlExpr ;
typedef  TYPE_8__ SSqlCmd ;
typedef  TYPE_9__ SSchema ;
typedef  TYPE_10__ SMeterMetaInfo ;

/* Variables and functions */
 int /*<<< orphan*/  MULTIPLE_APPEND_MODEL ; 
 int POINTER_BYTES ; 
 void* TSDB_CODE_CLI_OUT_OF_MEMORY ; 
 scalar_t__ TSDB_CODE_SUCCESS ; 
 scalar_t__ calloc (int,int) ; 
 scalar_t__ createOrderDescriptor (int /*<<< orphan*/ **,TYPE_8__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getTmpfilePath (char*,char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_9__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tColModelCreate (TYPE_9__*,size_t,size_t) ; 
 int /*<<< orphan*/  tExtMemBufferCreate (TYPE_3__**,size_t,size_t,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tfree (TYPE_9__*) ; 
 int /*<<< orphan*/  tscError (char*,TYPE_6__*) ; 
 TYPE_4__* tscFieldInfoGetField (TYPE_8__*,size_t) ; 
 TYPE_10__* tscGetMeterMetaInfo (TYPE_8__*,int /*<<< orphan*/ ) ; 
 TYPE_7__* tscSqlExprGet (TYPE_8__*,size_t) ; 
 int /*<<< orphan*/  tscTrace (char*,TYPE_6__*,size_t,size_t,char*) ; 

int32_t tscLocalReducerEnvCreate(SSqlObj *pSql, tExtMemBuffer ***pMemBuffer, tOrderDescriptor **pOrderDesc,
                                 tColModel **pFinalModel, uint32_t nBufferSizes) {
  SSqlCmd *pCmd = &pSql->cmd;
  SSqlRes *pRes = &pSql->res;

  SSchema *  pSchema = NULL;
  tColModel *pModel = NULL;
  *pFinalModel = NULL;

  SMeterMetaInfo *pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, 0);

  (*pMemBuffer) = (tExtMemBuffer **)malloc(POINTER_BYTES * pMeterMetaInfo->pMetricMeta->numOfVnodes);
  if (*pMemBuffer == NULL) {
    tscError("%p failed to allocate memory", pSql);
    pRes->code = TSDB_CODE_CLI_OUT_OF_MEMORY;
    return pRes->code;
  }

  pSchema = (SSchema *)calloc(1, sizeof(SSchema) * pCmd->fieldsInfo.numOfOutputCols);
  if (pSchema == NULL) {
    tscError("%p failed to allocate memory", pSql);
    pRes->code = TSDB_CODE_CLI_OUT_OF_MEMORY;
    return pRes->code;
  }

  int32_t rlen = 0;
  for (int32_t i = 0; i < pCmd->fieldsInfo.numOfOutputCols; ++i) {
    SSqlExpr *pExpr = tscSqlExprGet(pCmd, i);

    pSchema[i].bytes = pExpr->resBytes;
    pSchema[i].type = pExpr->resType;

    rlen += pExpr->resBytes;
  }

  int32_t capacity = nBufferSizes / rlen;
  pModel = tColModelCreate(pSchema, pCmd->fieldsInfo.numOfOutputCols, capacity);

  for (int32_t i = 0; i < pMeterMetaInfo->pMetricMeta->numOfVnodes; ++i) {
    char tmpPath[512] = {0};
    getTmpfilePath("tv_bf_db", tmpPath);
    tscTrace("%p create [%d](%d) tmp file for subquery:%s", pSql, pMeterMetaInfo->pMetricMeta->numOfVnodes, i, tmpPath);

    tExtMemBufferCreate(&(*pMemBuffer)[i], nBufferSizes, rlen, tmpPath, pModel);
    (*pMemBuffer)[i]->flushModel = MULTIPLE_APPEND_MODEL;
  }

  if (createOrderDescriptor(pOrderDesc, pCmd, pModel) != TSDB_CODE_SUCCESS) {
    pRes->code = TSDB_CODE_CLI_OUT_OF_MEMORY;
    return pRes->code;
  }

  memset(pSchema, 0, sizeof(SSchema) * pCmd->fieldsInfo.numOfOutputCols);
  for (int32_t i = 0; i < pCmd->fieldsInfo.numOfOutputCols; ++i) {
    TAOS_FIELD *pField = tscFieldInfoGetField(pCmd, i);

    pSchema[i].type = pField->type;
    pSchema[i].bytes = pField->bytes;
    strcpy(pSchema[i].name, pField->name);
  }

  *pFinalModel = tColModelCreate(pSchema, pCmd->fieldsInfo.numOfOutputCols, capacity);
  tfree(pSchema);

  return TSDB_CODE_SUCCESS;
}