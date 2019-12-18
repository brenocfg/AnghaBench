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
struct TYPE_15__ {TYPE_1__* pAcct; } ;
struct TYPE_14__ {void* numOfColumns; } ;
struct TYPE_13__ {void* bytes; int /*<<< orphan*/  name; void* type; } ;
struct TYPE_12__ {int* bytes; int numOfColumns; int* offset; int rowSize; int /*<<< orphan*/ * pNode; scalar_t__ numOfRows; } ;
struct TYPE_11__ {int /*<<< orphan*/  user; } ;
typedef  TYPE_2__ SShowObj ;
typedef  TYPE_3__ SSchema ;
typedef  TYPE_4__ SMeterMeta ;
typedef  int /*<<< orphan*/  SGlobalConfig ;
typedef  TYPE_5__ SConnObj ;

/* Variables and functions */
 int TSDB_CFG_OPTION_LEN ; 
 int TSDB_CFG_VALUE_LEN ; 
 int TSDB_CODE_NO_RIGHTS ; 
 void* TSDB_DATA_TYPE_BINARY ; 
 void* htons (int) ; 
 int /*<<< orphan*/  mgmtCheckConfigShow (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* tsGetSchema (TYPE_4__*) ; 
 int /*<<< orphan*/ * tsGlobalConfig ; 
 int tsGlobalConfigNum ; 

int mgmtGetConfigMeta(SMeterMeta *pMeta, SShowObj *pShow, SConnObj *pConn) {
  int cols = 0;

  if (strcmp(pConn->pAcct->user, "root") != 0) return TSDB_CODE_NO_RIGHTS;

  SSchema *pSchema = tsGetSchema(pMeta);

  pShow->bytes[cols] = TSDB_CFG_OPTION_LEN;
  pSchema[cols].type = TSDB_DATA_TYPE_BINARY;
  strcpy(pSchema[cols].name, "config name");
  pSchema[cols].bytes = htons(pShow->bytes[cols]);
  cols++;

  pShow->bytes[cols] = TSDB_CFG_VALUE_LEN;
  pSchema[cols].type = TSDB_DATA_TYPE_BINARY;
  strcpy(pSchema[cols].name, "config value");
  pSchema[cols].bytes = htons(pShow->bytes[cols]);
  cols++;

  pMeta->numOfColumns = htons(cols);
  pShow->numOfColumns = cols;

  pShow->offset[0] = 0;
  for (int i = 1; i < cols; ++i) pShow->offset[i] = pShow->offset[i - 1] + pShow->bytes[i - 1];

  pShow->numOfRows = 0;
  for (int i = tsGlobalConfigNum - 1; i >= 0; --i) {
    SGlobalConfig *cfg = tsGlobalConfig + i;
    if (!mgmtCheckConfigShow(cfg)) continue;
    pShow->numOfRows++;
  }

  pShow->rowSize = pShow->offset[cols - 1] + pShow->bytes[cols - 1];
  pShow->pNode = NULL;

  return 0;
}