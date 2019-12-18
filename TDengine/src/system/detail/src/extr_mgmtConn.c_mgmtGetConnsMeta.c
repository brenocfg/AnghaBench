#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {void* numOfColumns; } ;
struct TYPE_10__ {void* bytes; int /*<<< orphan*/  name; void* type; } ;
struct TYPE_9__ {int* bytes; int numOfColumns; int* offset; int numOfRows; int rowSize; int /*<<< orphan*/ * pNode; } ;
typedef  TYPE_1__ SShowObj ;
typedef  TYPE_2__ SSchema ;
typedef  TYPE_3__ SMeterMeta ;
typedef  int /*<<< orphan*/  SConnObj ;

/* Variables and functions */
 void* TSDB_DATA_TYPE_BINARY ; 
 void* TSDB_DATA_TYPE_TIMESTAMP ; 
 int TSDB_IPv4ADDR_LEN ; 
 int TSDB_METER_NAME_LEN ; 
 void* htons (int) ; 
 int /*<<< orphan*/  mgmtGetConns (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* tsGetSchema (TYPE_3__*) ; 

int mgmtGetConnsMeta(SMeterMeta *pMeta, SShowObj *pShow, SConnObj *pConn) {
  int cols = 0;

  pShow->bytes[cols] = TSDB_METER_NAME_LEN;
  SSchema *pSchema = tsGetSchema(pMeta);

  pSchema[cols].type = TSDB_DATA_TYPE_BINARY;
  strcpy(pSchema[cols].name, "user");
  pSchema[cols].bytes = htons(pShow->bytes[cols]);
  cols++;

  pShow->bytes[cols] = TSDB_IPv4ADDR_LEN + 6;
  pSchema[cols].type = TSDB_DATA_TYPE_BINARY;
  strcpy(pSchema[cols].name, "ip:port");
  pSchema[cols].bytes = htons(pShow->bytes[cols]);
  cols++;

  pShow->bytes[cols] = 8;
  pSchema[cols].type = TSDB_DATA_TYPE_TIMESTAMP;
  strcpy(pSchema[cols].name, "login time");
  pSchema[cols].bytes = htons(pShow->bytes[cols]);
  cols++;

  pMeta->numOfColumns = htons(cols);
  pShow->numOfColumns = cols;

  pShow->offset[0] = 0;
  for (int i = 1; i < cols; ++i) pShow->offset[i] = pShow->offset[i - 1] + pShow->bytes[i - 1];

  pShow->numOfRows = 1000000;
  pShow->pNode = NULL;
  pShow->rowSize = pShow->offset[cols - 1] + pShow->bytes[cols - 1];

  mgmtGetConns(pShow, pConn);
  return 0;
}