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
struct TYPE_10__ {char* name; } ;
struct TYPE_9__ {size_t status; int /*<<< orphan*/  privateIp; } ;
struct TYPE_8__ {int* offset; int* bytes; int numOfReads; int /*<<< orphan*/  pNode; } ;
typedef  TYPE_1__ SShowObj ;
typedef  TYPE_2__ SDnodeObj ;
typedef  int /*<<< orphan*/  SConnObj ;

/* Variables and functions */
 int TSDB_MOD_MAX ; 
 int /*<<< orphan*/  mgmtCheckModuleInDnode (TYPE_2__*,int) ; 
 int /*<<< orphan*/  mgmtGetNextDnode (TYPE_1__*,TYPE_2__**) ; 
 char** sdbDnodeStatusStr ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  tinet_ntoa (char*,int /*<<< orphan*/ ) ; 
 TYPE_3__* tsModule ; 

int mgmtRetrieveModules(SShowObj *pShow, char *data, int rows, SConnObj *pConn) {
  int        numOfRows = 0;
  SDnodeObj *pDnode = NULL;
  char *     pWrite;
  int        cols = 0;
  char       ipstr[20];

  while (numOfRows < rows) {
    pShow->pNode = mgmtGetNextDnode(pShow, (SDnodeObj **)&pDnode);
    if (pDnode == NULL) break;

    for (int moduleType = 0; moduleType < TSDB_MOD_MAX; ++moduleType) {
      if (!mgmtCheckModuleInDnode(pDnode, moduleType)) {
        continue;
      }

      cols = 0;

      tinet_ntoa(ipstr, pDnode->privateIp);
      pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
      strcpy(pWrite, ipstr);
      cols++;

      pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
      strcpy(pWrite, tsModule[moduleType].name);
      cols++;

      pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
      strcpy(pWrite, sdbDnodeStatusStr[pDnode->status]);
      cols++;

      numOfRows++;
    }
  }

  pShow->numOfReads += numOfRows;
  return numOfRows;
}