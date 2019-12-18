#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  meterId; int /*<<< orphan*/  peerId; int /*<<< orphan*/  ownId; int /*<<< orphan*/  tranId; struct TYPE_5__* signature; } ;
struct TYPE_4__ {int version; char msgType; scalar_t__ tranId; scalar_t__ content; int /*<<< orphan*/  meterId; scalar_t__ uid; int /*<<< orphan*/  destId; int /*<<< orphan*/  sourceId; scalar_t__ encrypt; scalar_t__ tcp; scalar_t__ spi; } ;
typedef  TYPE_1__ STaosHeader ;
typedef  int /*<<< orphan*/  STaosDigest ;
typedef  TYPE_2__ SRpcConn ;
typedef  int /*<<< orphan*/  SMsgNode ;

/* Variables and functions */
 void* atomic_add_fetch_32 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ getpid () ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  tError (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  tListLen (int /*<<< orphan*/ ) ; 

char *taosBuildReqMsgWithSize(void *param, char type, int size) {
  STaosHeader *pHeader;
  char *       pMsg;
  SRpcConn *   pConn = (SRpcConn *)param;

  if (pConn == NULL || pConn->signature != pConn) {
    tError("pConn:%p, connection has to be openned first before building a message", pConn);
    return NULL;
  }

  size += sizeof(SMsgNode) + sizeof(STaosHeader) + sizeof(STaosDigest);
  pMsg = (char *)malloc((size_t)size);
  memset(pMsg, 0, (size_t)size);
  pHeader = (STaosHeader *)(pMsg + sizeof(SMsgNode));
  pHeader->version = 1;
  pHeader->msgType = type;
  pHeader->spi = 0;
  pHeader->tcp = 0;
  pHeader->encrypt = 0;
  pHeader->tranId = atomic_add_fetch_32(&pConn->tranId, 1);
  if (pHeader->tranId == 0) pHeader->tranId = atomic_add_fetch_32(&pConn->tranId, 1);

  pHeader->sourceId = pConn->ownId;
  pHeader->destId = pConn->peerId;
  pHeader->uid = (uint32_t)pConn + (uint32_t)getpid();
  memcpy(pHeader->meterId, pConn->meterId, tListLen(pHeader->meterId));

  return (char *)pHeader->content;
}