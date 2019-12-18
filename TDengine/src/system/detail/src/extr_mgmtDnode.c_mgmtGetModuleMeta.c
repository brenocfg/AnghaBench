#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_1__* pAcct; } ;
struct TYPE_15__ {void* numOfColumns; } ;
struct TYPE_14__ {void* bytes; int /*<<< orphan*/  name; void* type; } ;
struct TYPE_13__ {int* bytes; int numOfColumns; int* offset; int rowSize; int /*<<< orphan*/ * pNode; scalar_t__ numOfRows; } ;
struct TYPE_12__ {int /*<<< orphan*/  user; } ;
typedef  TYPE_2__ SShowObj ;
typedef  TYPE_3__ SSchema ;
typedef  TYPE_4__ SMeterMeta ;
typedef  int /*<<< orphan*/  SDnodeObj ;
typedef  TYPE_5__ SConnObj ;

/* Variables and functions */
 int TSDB_CODE_NO_RIGHTS ; 
 void* TSDB_DATA_TYPE_BINARY ; 
 int TSDB_MOD_MAX ; 
 void* htons (int) ; 
 scalar_t__ mgmtCheckModuleInDnode (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * mgmtGetNextDnode (TYPE_2__*,int /*<<< orphan*/ **) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* tsGetSchema (TYPE_4__*) ; 

int mgmtGetModuleMeta(SMeterMeta *pMeta, SShowObj *pShow, SConnObj *pConn) {
  int cols = 0;

  if (strcmp(pConn->pAcct->user, "root") != 0) return TSDB_CODE_NO_RIGHTS;

  SSchema *pSchema = tsGetSchema(pMeta);

  pShow->bytes[cols] = 16;
  pSchema[cols].type = TSDB_DATA_TYPE_BINARY;
  strcpy(pSchema[cols].name, "IP");
  pSchema[cols].bytes = htons(pShow->bytes[cols]);
  cols++;

  pShow->bytes[cols] = 10;
  pSchema[cols].type = TSDB_DATA_TYPE_BINARY;
  strcpy(pSchema[cols].name, "module type");
  pSchema[cols].bytes = htons(pShow->bytes[cols]);
  cols++;

  pShow->bytes[cols] = 10;
  pSchema[cols].type = TSDB_DATA_TYPE_BINARY;
  strcpy(pSchema[cols].name, "module status");
  pSchema[cols].bytes = htons(pShow->bytes[cols]);
  cols++;

  pMeta->numOfColumns = htons(cols);
  pShow->numOfColumns = cols;

  pShow->offset[0] = 0;
  for (int i = 1; i < cols; ++i) pShow->offset[i] = pShow->offset[i - 1] + pShow->bytes[i - 1];

  pShow->numOfRows = 0;
  SDnodeObj *pDnode = NULL;
  while (1) {
    pShow->pNode = mgmtGetNextDnode(pShow, (SDnodeObj **)&pDnode);
    if (pDnode == NULL) break;
    for (int moduleType = 0; moduleType < TSDB_MOD_MAX; ++moduleType) {
      if (mgmtCheckModuleInDnode(pDnode, moduleType)) {
        pShow->numOfRows++;
      }
    }
  }

  pShow->rowSize = pShow->offset[cols - 1] + pShow->bytes[cols - 1];
  pShow->pNode = NULL;

  return 0;
}