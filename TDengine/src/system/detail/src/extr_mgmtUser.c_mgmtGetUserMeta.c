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
struct TYPE_17__ {TYPE_2__* pAcct; } ;
struct TYPE_16__ {void* numOfColumns; } ;
struct TYPE_15__ {void* bytes; int /*<<< orphan*/  name; void* type; } ;
struct TYPE_14__ {int* bytes; int numOfColumns; int* offset; int rowSize; int /*<<< orphan*/  pNode; int /*<<< orphan*/  numOfRows; } ;
struct TYPE_12__ {int /*<<< orphan*/  numOfUsers; } ;
struct TYPE_13__ {int /*<<< orphan*/  pUser; TYPE_1__ acctInfo; } ;
typedef  TYPE_3__ SShowObj ;
typedef  TYPE_4__ SSchema ;
typedef  TYPE_5__ SMeterMeta ;
typedef  TYPE_6__ SConnObj ;

/* Variables and functions */
 void* TSDB_DATA_TYPE_BINARY ; 
 void* TSDB_DATA_TYPE_TIMESTAMP ; 
 int TSDB_USER_LEN ; 
 void* htons (int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 TYPE_4__* tsGetSchema (TYPE_5__*) ; 

int mgmtGetUserMeta(SMeterMeta *pMeta, SShowObj *pShow, SConnObj *pConn) {
  int      cols = 0;
  SSchema *pSchema = tsGetSchema(pMeta);

  pShow->bytes[cols] = TSDB_USER_LEN;
  pSchema[cols].type = TSDB_DATA_TYPE_BINARY;
  strcpy(pSchema[cols].name, "name");
  pSchema[cols].bytes = htons(pShow->bytes[cols]);
  cols++;

  pShow->bytes[cols] = 6;
  pSchema[cols].type = TSDB_DATA_TYPE_BINARY;
  strcpy(pSchema[cols].name, "privilege");
  pSchema[cols].bytes = htons(pShow->bytes[cols]);
  cols++;

  pShow->bytes[cols] = 8;
  pSchema[cols].type = TSDB_DATA_TYPE_TIMESTAMP;
  strcpy(pSchema[cols].name, "created time");
  pSchema[cols].bytes = htons(pShow->bytes[cols]);
  cols++;

  pMeta->numOfColumns = htons(cols);
  pShow->numOfColumns = cols;

  pShow->offset[0] = 0;
  for (int i = 1; i < cols; ++i) pShow->offset[i] = pShow->offset[i - 1] + pShow->bytes[i - 1];

  //  pShow->numOfRows = sdbGetNumOfRows (userSdb);
  pShow->numOfRows = pConn->pAcct->acctInfo.numOfUsers;
  pShow->pNode = pConn->pAcct->pUser;
  pShow->rowSize = pShow->offset[cols - 1] + pShow->bytes[cols - 1];

  return 0;
}