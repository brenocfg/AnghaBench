#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_1__* pDb; } ;
struct TYPE_16__ {void* numOfColumns; } ;
struct TYPE_15__ {void* bytes; int /*<<< orphan*/  name; void* type; } ;
struct TYPE_14__ {int* bytes; int numOfColumns; int* offset; int rowSize; TYPE_2__* pNode; int /*<<< orphan*/  numOfRows; } ;
struct TYPE_13__ {int numOfVnodes; struct TYPE_13__* next; } ;
struct TYPE_12__ {TYPE_2__* pHead; int /*<<< orphan*/  numOfVgroups; } ;
typedef  TYPE_2__ SVgObj ;
typedef  TYPE_3__ SShowObj ;
typedef  TYPE_4__ SSchema ;
typedef  TYPE_5__ SMeterMeta ;
typedef  TYPE_6__ SConnObj ;

/* Variables and functions */
 int TSDB_CODE_DB_NOT_SELECTED ; 
 void* TSDB_DATA_TYPE_BINARY ; 
 void* TSDB_DATA_TYPE_INT ; 
 void* TSDB_DATA_TYPE_SMALLINT ; 
 void* htons (int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 TYPE_4__* tsGetSchema (TYPE_5__*) ; 

int mgmtGetVgroupMeta(SMeterMeta *pMeta, SShowObj *pShow, SConnObj *pConn) {
  int cols = 0;

  if (pConn->pDb == NULL) return TSDB_CODE_DB_NOT_SELECTED;

  SSchema *pSchema = tsGetSchema(pMeta);

  pShow->bytes[cols] = 4;
  pSchema[cols].type = TSDB_DATA_TYPE_INT;
  strcpy(pSchema[cols].name, "vgId");
  pSchema[cols].bytes = htons(pShow->bytes[cols]);
  cols++;

  pShow->bytes[cols] = 4;
  pSchema[cols].type = TSDB_DATA_TYPE_INT;
  strcpy(pSchema[cols].name, "meters");
  pSchema[cols].bytes = htons(pShow->bytes[cols]);
  cols++;

  pShow->bytes[cols] = 9;
  pSchema[cols].type = TSDB_DATA_TYPE_BINARY;
  strcpy(pSchema[cols].name, "vgroup status");
  pSchema[cols].bytes = htons(pShow->bytes[cols]);
  cols++;

  int     maxReplica = 0;
  SVgObj *pVgroup = pConn->pDb->pHead;
  while (pVgroup != NULL) {
    maxReplica = pVgroup->numOfVnodes > maxReplica ? pVgroup->numOfVnodes : maxReplica;
    pVgroup = pVgroup->next;
  }

  for (int i = 0; i < maxReplica; ++i) {
    pShow->bytes[cols] = 16;
    pSchema[cols].type = TSDB_DATA_TYPE_BINARY;
    strcpy(pSchema[cols].name, "ip");
    pSchema[cols].bytes = htons(pShow->bytes[cols]);
    cols++;

    pShow->bytes[cols] = 2;
    pSchema[cols].type = TSDB_DATA_TYPE_SMALLINT;
    strcpy(pSchema[cols].name, "vnode");
    pSchema[cols].bytes = htons(pShow->bytes[cols]);
    cols++;

    pShow->bytes[cols] = 9;
    pSchema[cols].type = TSDB_DATA_TYPE_BINARY;
    strcpy(pSchema[cols].name, "vnode status");
    pSchema[cols].bytes = htons(pShow->bytes[cols]);
    cols++;

    pShow->bytes[cols] = 16;
    pSchema[cols].type = TSDB_DATA_TYPE_BINARY;
    strcpy(pSchema[cols].name, "public ip");
    pSchema[cols].bytes = htons(pShow->bytes[cols]);
    cols++;
  }

  pMeta->numOfColumns = htons(cols);
  pShow->numOfColumns = cols;

  pShow->offset[0] = 0;
  for (int i = 1; i < cols; ++i) pShow->offset[i] = pShow->offset[i - 1] + pShow->bytes[i - 1];

  pShow->numOfRows = pConn->pDb->numOfVgroups;
  pShow->pNode = pConn->pDb->pHead;
  pShow->rowSize = pShow->offset[cols - 1] + pShow->bytes[cols - 1];

  return 0;
}