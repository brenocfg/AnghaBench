#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  void* int32_t ;
struct TYPE_7__ {char* pQuickRsp; int /*<<< orphan*/  secret; scalar_t__ spi; } ;
struct TYPE_6__ {int /*<<< orphan*/  auth; scalar_t__ timeStamp; } ;
struct TYPE_5__ {void* msgLen; scalar_t__ spi; } ;
typedef  TYPE_1__ STaosHeader ;
typedef  TYPE_2__ STaosDigest ;
typedef  TYPE_3__ SRpcConn ;

/* Variables and functions */
 scalar_t__ TSDB_AUTH_LEN ; 
 scalar_t__ htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosBuildAuthHeader (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* taosBuildRspMsgWithSize (void*,char,int) ; 
 int /*<<< orphan*/  taosGetTimestampSec () ; 
 int /*<<< orphan*/  taosSendDataToPeer (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  tfree (char*) ; 

int taosSendQuickRsp(void *thandle, char rsptype, char code) {
  char *       pCont;
  int          contLen;
  STaosHeader *pHeader;
  char *       msg;
  int          msgLen;
  SRpcConn *   pConn = (SRpcConn *)thandle;

  pCont = taosBuildRspMsgWithSize(thandle, rsptype, 32);
  if (pCont == NULL) return 0;

  *pCont = code;
  contLen = 1;

  pHeader = (STaosHeader *)(pCont - sizeof(STaosHeader));
  msg = (char *)pHeader;
  msgLen = contLen + (int32_t)sizeof(STaosHeader);

  if (pConn->spi) {
    // add auth part
    pHeader->spi = pConn->spi;
    STaosDigest *pDigest = (STaosDigest *)(pCont + contLen);
    pDigest->timeStamp = htonl(taosGetTimestampSec());
    msgLen += sizeof(STaosDigest);
    pHeader->msgLen = (int32_t)htonl((uint32_t)msgLen);
    taosBuildAuthHeader((uint8_t *)pHeader, msgLen - TSDB_AUTH_LEN, pDigest->auth, pConn->secret);
  } else {
    pHeader->msgLen = (int32_t)htonl((uint32_t)msgLen);
  }

  tfree(pConn->pQuickRsp);
  pConn->pQuickRsp = msg;
  taosSendDataToPeer(pConn, (char *)pHeader, msgLen);

  return msgLen;
}