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
struct TYPE_5__ {int /*<<< orphan*/  meterId; int /*<<< orphan*/  peerId; int /*<<< orphan*/  ownId; int /*<<< orphan*/  inTranId; struct TYPE_5__* signature; } ;
struct TYPE_4__ {int version; char msgType; scalar_t__ content; int /*<<< orphan*/  meterId; scalar_t__ uid; int /*<<< orphan*/  destId; int /*<<< orphan*/  sourceId; int /*<<< orphan*/  tranId; scalar_t__ encrypt; scalar_t__ tcp; scalar_t__ spi; } ;
typedef  TYPE_1__ STaosHeader ;
typedef  int /*<<< orphan*/  STaosDigest ;
typedef  TYPE_2__ SRpcConn ;
typedef  int /*<<< orphan*/  SMsgNode ;

/* Variables and functions */
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  tError (char*,TYPE_2__*,...) ; 
 int /*<<< orphan*/  tListLen (int /*<<< orphan*/ ) ; 

char *taosBuildRspMsgWithSize(void *param, char type, int size) {
  STaosHeader *pHeader;
  char *       pMsg;
  SRpcConn *   pConn = (SRpcConn *)param;

  if (pConn == NULL || pConn->signature != pConn) {
    tError("pConn:%p, connection has to be opened first before building a message", pConn);
    return NULL;
  }

  size += sizeof(SMsgNode) + sizeof(STaosHeader) + sizeof(STaosDigest);
  pMsg = (char *)malloc((size_t)size);
  if (pMsg == NULL) {
    tError("pConn:%p, malloc(%d) failed when building a type:%d message", pConn, size, type);
    return NULL;
  }

  memset(pMsg, 0, (size_t)size);
  pHeader = (STaosHeader *)pMsg;
  pHeader->version = 1;
  pHeader->msgType = type;
  pHeader->spi = 0;
  pHeader->tcp = 0;
  pHeader->encrypt = 0;
  pHeader->tranId = pConn->inTranId;
  pHeader->sourceId = pConn->ownId;
  pHeader->destId = pConn->peerId;
  pHeader->uid = 0;
  memcpy(pHeader->meterId, pConn->meterId, tListLen(pHeader->meterId));

  return (char *)pHeader->content;
}