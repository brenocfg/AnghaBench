#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_1__* pDb; } ;
struct TYPE_14__ {void* numOfColumns; } ;
struct TYPE_13__ {void* bytes; int /*<<< orphan*/  name; void* type; } ;
struct TYPE_12__ {int* bytes; int numOfColumns; int* offset; int rowSize; int /*<<< orphan*/  pNode; int /*<<< orphan*/  numOfRows; } ;
struct TYPE_11__ {int /*<<< orphan*/  pMetric; int /*<<< orphan*/  numOfMetrics; } ;
typedef  TYPE_2__ SShowObj ;
typedef  TYPE_3__ SSchema ;
typedef  TYPE_4__ SMeterMeta ;
typedef  TYPE_5__ SConnObj ;

/* Variables and functions */
 int TSDB_CODE_DB_NOT_SELECTED ; 
 void* TSDB_DATA_TYPE_BINARY ; 
 void* TSDB_DATA_TYPE_INT ; 
 void* TSDB_DATA_TYPE_SMALLINT ; 
 void* TSDB_DATA_TYPE_TIMESTAMP ; 
 int TSDB_METER_NAME_LEN ; 
 void* htons (int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* tsGetSchema (TYPE_4__*) ; 

int mgmtGetMetricMeta(SMeterMeta *pMeta, SShowObj *pShow, SConnObj *pConn) {
  int cols = 0;

  if (pConn->pDb == NULL) return TSDB_CODE_DB_NOT_SELECTED;

  SSchema *pSchema = tsGetSchema(pMeta);

  pShow->bytes[cols] = TSDB_METER_NAME_LEN;
  pSchema[cols].type = TSDB_DATA_TYPE_BINARY;
  strcpy(pSchema[cols].name, "name");
  pSchema[cols].bytes = htons(pShow->bytes[cols]);
  cols++;

  pShow->bytes[cols] = 8;
  pSchema[cols].type = TSDB_DATA_TYPE_TIMESTAMP;
  strcpy(pSchema[cols].name, "created_time");
  pSchema[cols].bytes = htons(pShow->bytes[cols]);
  cols++;

  pShow->bytes[cols] = 2;
  pSchema[cols].type = TSDB_DATA_TYPE_SMALLINT;
  strcpy(pSchema[cols].name, "columns");
  pSchema[cols].bytes = htons(pShow->bytes[cols]);
  cols++;

  pShow->bytes[cols] = 2;
  pSchema[cols].type = TSDB_DATA_TYPE_SMALLINT;
  strcpy(pSchema[cols].name, "tags");
  pSchema[cols].bytes = htons(pShow->bytes[cols]);
  cols++;

  pShow->bytes[cols] = 4;
  pSchema[cols].type = TSDB_DATA_TYPE_INT;
  strcpy(pSchema[cols].name, "tables");
  pSchema[cols].bytes = htons(pShow->bytes[cols]);
  cols++;

  pMeta->numOfColumns = htons(cols);
  pShow->numOfColumns = cols;

  pShow->offset[0] = 0;
  for (int i = 1; i < cols; ++i) pShow->offset[i] = pShow->offset[i - 1] + pShow->bytes[i - 1];

  pShow->numOfRows = pConn->pDb->numOfMetrics;
  pShow->pNode = pConn->pDb->pMetric;
  pShow->rowSize = pShow->offset[cols - 1] + pShow->bytes[cols - 1];

  return 0;
}