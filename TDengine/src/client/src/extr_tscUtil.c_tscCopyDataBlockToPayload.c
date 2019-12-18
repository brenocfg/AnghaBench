#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_14__ {int /*<<< orphan*/  name; } ;
struct TYPE_13__ {scalar_t__ payloadLen; scalar_t__ allocSize; int /*<<< orphan*/  payload; int /*<<< orphan*/  count; } ;
struct TYPE_12__ {TYPE_3__ cmd; } ;
struct TYPE_11__ {scalar_t__ nAllocSize; int /*<<< orphan*/  pData; int /*<<< orphan*/  meterId; int /*<<< orphan*/  numOfMeters; } ;
typedef  int /*<<< orphan*/  STaosDigest ;
typedef  TYPE_1__ STableDataBlocks ;
typedef  TYPE_2__ SSqlObj ;
typedef  TYPE_3__ SSqlCmd ;
typedef  TYPE_4__ SMeterMetaInfo ;

/* Variables and functions */
 int TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tsRpcHeadSize ; 
 int tscAllocPayload (TYPE_3__*,scalar_t__) ; 
 int tscGetMeterMeta (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* tscGetMeterMetaInfo (TYPE_3__*,int /*<<< orphan*/ ) ; 

int32_t tscCopyDataBlockToPayload(SSqlObj* pSql, STableDataBlocks* pDataBlock) {
  SSqlCmd* pCmd = &pSql->cmd;

  pCmd->count = pDataBlock->numOfMeters;
  SMeterMetaInfo* pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, 0);
  strcpy(pMeterMetaInfo->name, pDataBlock->meterId);

  /*
   * the submit message consists of : [RPC header|message body|digest]
   * the dataBlock only includes the RPC Header buffer and actual submit messsage body, space for digest needs
   * additional space.
   */
  int ret = tscAllocPayload(pCmd, pDataBlock->nAllocSize + sizeof(STaosDigest));
  if (TSDB_CODE_SUCCESS != ret) return ret;
  memcpy(pCmd->payload, pDataBlock->pData, pDataBlock->nAllocSize);

  /*
   * the payloadLen should be actual message body size
   * the old value of payloadLen is the allocated payload size
   */
  pCmd->payloadLen = pDataBlock->nAllocSize - tsRpcHeadSize;

  assert(pCmd->allocSize >= pCmd->payloadLen + tsRpcHeadSize + sizeof(STaosDigest));
  return tscGetMeterMeta(pSql, pMeterMetaInfo->name, 0);
}