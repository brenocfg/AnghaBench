#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_7__ {size_t status; size_t lbState; int /*<<< orphan*/  publicIp; int /*<<< orphan*/  numOfFreeVnodes; int /*<<< orphan*/  openVnodes; int /*<<< orphan*/  createdTime; int /*<<< orphan*/  privateIp; } ;
struct TYPE_6__ {int* offset; int* bytes; int numOfReads; int /*<<< orphan*/  pNode; } ;
typedef  TYPE_1__ SShowObj ;
typedef  TYPE_2__ SDnodeObj ;
typedef  int /*<<< orphan*/  SConnObj ;

/* Variables and functions */
 int /*<<< orphan*/  mgmtGetNextDnode (TYPE_1__*,TYPE_2__**) ; 
 char** sdbDnodeBalanceStateStr ; 
 char** sdbDnodeStatusStr ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  tinet_ntoa (char*,int /*<<< orphan*/ ) ; 

int mgmtRetrieveDnodes(SShowObj *pShow, char *data, int rows, SConnObj *pConn) {
  int        numOfRows = 0;
  SDnodeObj *pDnode = NULL;
  char *     pWrite;
  int        cols = 0;
  char       ipstr[20];

  while (numOfRows < rows) {
    pShow->pNode = mgmtGetNextDnode(pShow, (SDnodeObj **)&pDnode);
    if (pDnode == NULL) break;

    cols = 0;

    tinet_ntoa(ipstr, pDnode->privateIp);
    pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
    strcpy(pWrite, ipstr);
    cols++;

    pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
    *(int64_t *)pWrite = pDnode->createdTime;
    cols++;

    pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
    *(int16_t *)pWrite = pDnode->openVnodes;
    cols++;

    pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
    *(int16_t *)pWrite = pDnode->numOfFreeVnodes;
    cols++;

    pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
    strcpy(pWrite, sdbDnodeStatusStr[pDnode->status]);
    cols++;

    pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
    strcpy(pWrite, sdbDnodeBalanceStateStr[pDnode->lbState]);
    cols++;

    tinet_ntoa(ipstr, pDnode->publicIp);
    pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
    strcpy(pWrite, ipstr);
    cols++;

    numOfRows++;
  }

  pShow->numOfReads += numOfRows;
  return numOfRows;
}