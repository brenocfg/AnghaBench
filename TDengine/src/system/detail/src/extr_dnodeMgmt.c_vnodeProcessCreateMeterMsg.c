#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int bytes; void* colId; int /*<<< orphan*/  type; } ;
struct TYPE_17__ {char* secret; char* cipheringKey; int /*<<< orphan*/  encrypt; int /*<<< orphan*/  spi; } ;
struct TYPE_16__ {int vnode; scalar_t__ sid; char* meterId; int numOfColumns; int sqlLen; scalar_t__ sversion; char* secret; char* cipheringKey; int /*<<< orphan*/  encrypt; int /*<<< orphan*/  spi; TYPE_2__* schema; void* timeStamp; int /*<<< orphan*/  uid; void* lastCreate; } ;
struct TYPE_15__ {int vnode; scalar_t__ sid; char* meterId; int numOfColumns; scalar_t__ maxBytes; int sqlLen; char* pSql; TYPE_7__* schema; int /*<<< orphan*/  pointsPerFileBlock; int /*<<< orphan*/  bytesPerPoint; void* sversion; void* timeStamp; int /*<<< orphan*/  uid; } ;
struct TYPE_12__ {scalar_t__ maxSessions; int /*<<< orphan*/  rowsInFileBlock; } ;
struct TYPE_14__ {TYPE_1__ cfg; int /*<<< orphan*/ * pCachePool; } ;
struct TYPE_13__ {int bytes; int colId; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  TSKEY ;
typedef  TYPE_3__ SVnodeObj ;
typedef  TYPE_4__ SMeterObj ;
typedef  int /*<<< orphan*/  SMColumn ;
typedef  TYPE_5__ SCreateMsg ;
typedef  TYPE_6__ SConnSec ;
typedef  TYPE_7__ SColumn ;

/* Variables and functions */
 int TSDB_CODE_INVALID_SESSION_ID ; 
 int TSDB_CODE_NOT_ACTIVE_SESSION ; 
 int TSDB_CODE_NO_RESOURCE ; 
 int TSDB_CODE_OTHERS ; 
 int TSDB_CODE_SUCCESS ; 
 int TSDB_KEY_LEN ; 
 scalar_t__ TSDB_MAX_VNODES ; 
 int TSDB_METER_ID_LEN ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  dError (char*,int,...) ; 
 int /*<<< orphan*/  dTrace (char*,int,scalar_t__,char*) ; 
 void* htobe64 (void*) ; 
 void* htonl (scalar_t__) ; 
 void* htons (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  tfree (TYPE_4__*) ; 
 int vnodeCreateMeterObj (TYPE_4__*,TYPE_6__*) ; 
 TYPE_3__* vnodeList ; 
 int /*<<< orphan*/  vnodeSendVpeerCfgMsg (int) ; 

int vnodeProcessCreateMeterMsg(char *pMsg, int msgLen) {
  int         code;
  SMeterObj * pObj = NULL;
  SConnSec    connSec;
  SCreateMsg *pCreate = (SCreateMsg *)pMsg;

  pCreate->vnode = htons(pCreate->vnode);
  pCreate->sid = htonl(pCreate->sid);
  pCreate->lastCreate = htobe64(pCreate->lastCreate);
  pCreate->timeStamp = htobe64(pCreate->timeStamp);

  if (pCreate->vnode >= TSDB_MAX_VNODES || pCreate->vnode < 0) {
    dError("vid:%d is out of range", pCreate->vnode);
    code = TSDB_CODE_INVALID_SESSION_ID;
    goto _create_over;
  }

  SVnodeObj *pVnode = vnodeList + pCreate->vnode;
  if (pVnode->pCachePool == NULL) {
    dError("vid:%d is not activated yet", pCreate->vnode);
    vnodeSendVpeerCfgMsg(pCreate->vnode);
    code = TSDB_CODE_NOT_ACTIVE_SESSION;
    goto _create_over;
  }

  if (pCreate->sid >= pVnode->cfg.maxSessions || pCreate->sid < 0) {
    dError("vid:%d sid:%d id:%s, sid is out of range", pCreate->vnode, pCreate->sid, pCreate->meterId);
    code = TSDB_CODE_INVALID_SESSION_ID;
    goto _create_over;
  }

  pCreate->numOfColumns = htons(pCreate->numOfColumns);
  if (pCreate->numOfColumns <= 0) {
    dTrace("vid:%d sid:%d id:%s, numOfColumns is out of range", pCreate->vnode, pCreate->sid, pCreate->meterId);
    code = TSDB_CODE_OTHERS;
    goto _create_over;
  }

  pCreate->sqlLen = htons(pCreate->sqlLen);
  pObj = (SMeterObj *)calloc(1, sizeof(SMeterObj) + pCreate->sqlLen + 1);
  if (pObj == NULL) {
    dError("vid:%d sid:%d id:%s, no memory to allocate meterObj", pCreate->vnode, pCreate->sid, pCreate->meterId);
    code = TSDB_CODE_NO_RESOURCE;
    goto _create_over;
  }

  /*
   * memory alignment may cause holes in SColumn struct which are not assigned any value
   * therefore, we could not use memcmp to compare whether two SColumns are equal or not.
   * So, we need to set the memory to 0 when allocating memory.
   */
  pObj->schema = (SColumn *)calloc(1, pCreate->numOfColumns * sizeof(SColumn));

  pObj->vnode = pCreate->vnode;
  pObj->sid = pCreate->sid;
  pObj->uid = pCreate->uid;
  memcpy(pObj->meterId, pCreate->meterId, TSDB_METER_ID_LEN);
  pObj->numOfColumns = pCreate->numOfColumns;
  pObj->timeStamp = pCreate->timeStamp;
  pObj->sversion = htonl(pCreate->sversion);
  pObj->maxBytes = 0;

  for (int i = 0; i < pObj->numOfColumns; ++i) {
    pObj->schema[i].type = pCreate->schema[i].type;
    pObj->schema[i].bytes = htons(pCreate->schema[i].bytes);
    pObj->schema[i].colId = htons(pCreate->schema[i].colId);
    pObj->bytesPerPoint += pObj->schema[i].bytes;
    if (pObj->maxBytes < pObj->schema[i].bytes) pObj->maxBytes = pObj->schema[i].bytes;
  }

  if (pCreate->sqlLen > 0) {
    pObj->sqlLen = pCreate->sqlLen;
    pObj->pSql = ((char *)pObj) + sizeof(SMeterObj);
    memcpy(pObj->pSql, (char *)pCreate->schema + pCreate->numOfColumns * sizeof(SMColumn), pCreate->sqlLen);
    pObj->pSql[pCreate->sqlLen] = 0;
  }

  pObj->pointsPerFileBlock = pVnode->cfg.rowsInFileBlock;

  if (sizeof(TSKEY) != pObj->schema[0].bytes) {
    dError("key length is not matched, required key length:%d", sizeof(TSKEY));
    code = TSDB_CODE_OTHERS;
    goto _create_over;
  }

  // security info shall be saved here
  connSec.spi = pCreate->spi;
  connSec.encrypt = pCreate->encrypt;
  memcpy(connSec.secret, pCreate->secret, TSDB_KEY_LEN);
  memcpy(connSec.cipheringKey, pCreate->cipheringKey, TSDB_KEY_LEN);

  code = vnodeCreateMeterObj(pObj, &connSec);

_create_over:
  if (code != TSDB_CODE_SUCCESS) {
    dTrace("vid:%d sid:%d id:%s, failed to create meterObj", pCreate->vnode, pCreate->sid, pCreate->meterId);
    tfree(pObj);
  }

  return code;
}