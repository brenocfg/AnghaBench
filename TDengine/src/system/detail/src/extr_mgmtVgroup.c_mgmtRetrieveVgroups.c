#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_13__ {scalar_t__ ip; scalar_t__ publicIp; int /*<<< orphan*/  vnode; } ;
struct TYPE_12__ {TYPE_1__* pDb; } ;
struct TYPE_11__ {int* offset; int* bytes; int numOfReads; void* pNode; } ;
struct TYPE_10__ {int numOfVnodes; TYPE_8__* vnodeGid; scalar_t__ lbState; int /*<<< orphan*/  numOfMeters; int /*<<< orphan*/  vgId; struct TYPE_10__* next; } ;
struct TYPE_9__ {TYPE_2__* pHead; } ;
typedef  TYPE_2__ SVgObj ;
typedef  TYPE_3__ SShowObj ;
typedef  TYPE_4__ SConnObj ;

/* Variables and functions */
 int mgmtCheckVnodeReady (int /*<<< orphan*/ *,TYPE_2__*,TYPE_8__*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  tinet_ntoa (char*,scalar_t__) ; 

int mgmtRetrieveVgroups(SShowObj *pShow, char *data, int rows, SConnObj *pConn) {
  int     numOfRows = 0;
  SVgObj *pVgroup = NULL;
  char *  pWrite;
  int     cols = 0;
  char    ipstr[20];

  int maxReplica = 0;
  pVgroup = pConn->pDb->pHead;
  while (pVgroup != NULL) {
    maxReplica = pVgroup->numOfVnodes > maxReplica ? pVgroup->numOfVnodes : maxReplica;
    pVgroup = pVgroup->next;
  }

  while (numOfRows < rows) {
    //    pShow->pNode = sdbFetchRow(vgSdb, pShow->pNode, (void **)&pVgroup);
    pVgroup = (SVgObj *)pShow->pNode;
    if (pVgroup == NULL) break;
    pShow->pNode = (void *)pVgroup->next;

    cols = 0;

    pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
    *(int32_t *)pWrite = pVgroup->vgId;
    cols++;

    pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
    *(int32_t *)pWrite = pVgroup->numOfMeters;
    cols++;

    pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
    strcpy(pWrite, pVgroup->lbState ? "updating" : "ready");
    cols++;

    for (int i = 0; i < maxReplica; ++i) {
      tinet_ntoa(ipstr, pVgroup->vnodeGid[i].ip);
      pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
      strcpy(pWrite, ipstr);
      cols++;

      pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
      *(int16_t *)pWrite = pVgroup->vnodeGid[i].vnode;
      cols++;

      pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
      if (pVgroup->vnodeGid[i].ip != 0) {
        bool ready = mgmtCheckVnodeReady(NULL, pVgroup, pVgroup->vnodeGid + i);
        strcpy(pWrite, ready ? "ready" : "unsynced");
      } else {
        strcpy(pWrite, "null");
      }
      cols++;

      tinet_ntoa(ipstr, pVgroup->vnodeGid[i].publicIp);
      pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
      strcpy(pWrite, ipstr);
      cols++;
    }

    numOfRows++;
  }

  pShow->numOfReads += numOfRows;
  return numOfRows;
}