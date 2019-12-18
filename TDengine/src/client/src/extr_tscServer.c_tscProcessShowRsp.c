#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_13__ ;

/* Type definitions */
typedef  int int32_t ;
typedef  size_t int16_t ;
struct TYPE_28__ {size_t columnIndex; int /*<<< orphan*/  member_0; } ;
struct TYPE_27__ {int numOfColumns; int sid; } ;
struct TYPE_26__ {TYPE_7__* pMeterMeta; } ;
struct TYPE_25__ {int /*<<< orphan*/  bytes; } ;
struct TYPE_24__ {TYPE_7__ meterMeta; int /*<<< orphan*/  qhandle; } ;
struct TYPE_20__ {int /*<<< orphan*/  numOfOutputCols; } ;
struct TYPE_23__ {char showType; TYPE_13__ fieldsInfo; int /*<<< orphan*/  colList; int /*<<< orphan*/  numOfCols; } ;
struct TYPE_21__ {int /*<<< orphan*/  qhandle; scalar_t__ pRsp; } ;
struct TYPE_22__ {TYPE_3__ cmd; TYPE_1__ res; } ;
typedef  TYPE_1__ SSqlRes ;
typedef  TYPE_2__ SSqlObj ;
typedef  TYPE_3__ SSqlCmd ;
typedef  TYPE_4__ SShowRspMsg ;
typedef  TYPE_5__ SSchema ;
typedef  TYPE_6__ SMeterMetaInfo ;
typedef  TYPE_7__ SMeterMeta ;
typedef  TYPE_8__ SColumnIndex ;

/* Variables and functions */
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 void* ntohs (int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ taosAddDataIntoCache (int /*<<< orphan*/ ,char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosRemoveDataFromCache (int /*<<< orphan*/ ,void*,int) ; 
 TYPE_5__* tsGetSchema (TYPE_7__*) ; 
 int /*<<< orphan*/  tsMeterMetaKeepTimer ; 
 int /*<<< orphan*/  tscCacheHandle ; 
 int /*<<< orphan*/  tscColumnBaseInfoInsert (TYPE_3__*,TYPE_8__*) ; 
 int /*<<< orphan*/  tscColumnBaseInfoReserve (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tscFieldInfoCalOffset (TYPE_3__*) ; 
 int /*<<< orphan*/  tscFieldInfoSetValFromSchema (TYPE_13__*,size_t,TYPE_5__*) ; 
 TYPE_6__* tscGetMeterMetaInfo (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscResetForNextRetrieve (TYPE_1__*) ; 

int tscProcessShowRsp(SSqlObj *pSql) {
  SMeterMeta * pMeta;
  SShowRspMsg *pShow;
  SSchema *    pSchema;
  char         key[20];

  SSqlRes *       pRes = &pSql->res;
  SSqlCmd *       pCmd = &pSql->cmd;
  SMeterMetaInfo *pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, 0);

  pShow = (SShowRspMsg *)pRes->pRsp;
  pRes->qhandle = pShow->qhandle;

  tscResetForNextRetrieve(pRes);
  pMeta = &(pShow->meterMeta);

  pMeta->numOfColumns = ntohs(pMeta->numOfColumns);

  pSchema = (SSchema *)((char *)pMeta + sizeof(SMeterMeta));
  pMeta->sid = ntohs(pMeta->sid);
  for (int i = 0; i < pMeta->numOfColumns; ++i) {
    pSchema->bytes = htons(pSchema->bytes);
    pSchema++;
  }

  key[0] = pCmd->showType + 'a';
  strcpy(key + 1, "showlist");

  taosRemoveDataFromCache(tscCacheHandle, (void *)&(pMeterMetaInfo->pMeterMeta), false);

  int32_t size = pMeta->numOfColumns * sizeof(SSchema) + sizeof(SMeterMeta);
  pMeterMetaInfo->pMeterMeta =
      (SMeterMeta *)taosAddDataIntoCache(tscCacheHandle, key, (char *)pMeta, size, tsMeterMetaKeepTimer);
  pCmd->numOfCols = pCmd->fieldsInfo.numOfOutputCols;
  SSchema *pMeterSchema = tsGetSchema(pMeterMetaInfo->pMeterMeta);

  tscColumnBaseInfoReserve(&pCmd->colList, pMeta->numOfColumns);
  SColumnIndex index = {0};

  for (int16_t i = 0; i < pMeta->numOfColumns; ++i) {
    index.columnIndex = i;
    tscColumnBaseInfoInsert(pCmd, &index);
    tscFieldInfoSetValFromSchema(&pCmd->fieldsInfo, i, &pMeterSchema[i]);
  }

  tscFieldInfoCalOffset(pCmd);
  return 0;
}