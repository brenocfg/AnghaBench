#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_10__ {int /*<<< orphan*/  numOfTags; int /*<<< orphan*/  numOfColumns; } ;
struct TYPE_9__ {TYPE_3__* pMeterMeta; } ;
struct TYPE_8__ {int /*<<< orphan*/ * pStream; int /*<<< orphan*/ * fp; int /*<<< orphan*/  cmd; } ;
typedef  TYPE_1__ SSqlObj ;
typedef  int /*<<< orphan*/  SSqlCmd ;
typedef  TYPE_2__ SMeterMetaInfo ;
typedef  TYPE_3__ SMeterMeta ;

/* Variables and functions */
 int TSDB_CODE_SUCCESS ; 
 scalar_t__ taosGetDataFromCache (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  taosRemoveDataFromCache (int /*<<< orphan*/ ,void**,int) ; 
 int /*<<< orphan*/  tscCacheHandle ; 
 int tscDoGetMeterMeta (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscFreeSqlCmdData (int /*<<< orphan*/ *) ; 
 TYPE_2__* tscGetMeterMetaInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscTrace (char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tscGetMeterMeta(SSqlObj *pSql, char *meterId, int32_t index) {
  SSqlCmd *       pCmd = &pSql->cmd;
  SMeterMetaInfo *pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, index);

  // if the SSqlCmd owns a metermeta, release it first
  taosRemoveDataFromCache(tscCacheHandle, (void **)&(pMeterMetaInfo->pMeterMeta), false);
  pMeterMetaInfo->pMeterMeta = (SMeterMeta *)taosGetDataFromCache(tscCacheHandle, meterId);

  if (pMeterMetaInfo->pMeterMeta != NULL) {
    SMeterMeta *pMeterMeta = pMeterMetaInfo->pMeterMeta;

    tscTrace("%p retrieve meterMeta from cache, the number of columns:%d, numOfTags:%d", pSql, pMeterMeta->numOfColumns,
             pMeterMeta->numOfTags);

    return TSDB_CODE_SUCCESS;
  }

  /*
   * for async insert operation, release data block buffer before issue new object to get metermeta
   * because in metermeta callback function, the tscParse function will generate the submit data blocks
   */
  if (pSql->fp != NULL && pSql->pStream == NULL) {
    tscFreeSqlCmdData(pCmd);
  }

  return tscDoGetMeterMeta(pSql, meterId, index);
}