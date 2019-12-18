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
typedef  int uint32_t ;
typedef  int int32_t ;
typedef  int int16_t ;
struct TYPE_7__ {char* option; int valType; scalar_t__ ptr; } ;
struct TYPE_6__ {int* offset; int* bytes; int numOfReads; } ;
typedef  TYPE_1__ SShowObj ;
typedef  TYPE_2__ SGlobalConfig ;
typedef  int /*<<< orphan*/  SConnObj ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_CFG_OPTION_LEN ; 
 int /*<<< orphan*/  TSDB_CFG_VALUE_LEN ; 
#define  TSDB_CFG_VTYPE_DIRECTORY 134 
#define  TSDB_CFG_VTYPE_FLOAT 133 
#define  TSDB_CFG_VTYPE_INT 132 
#define  TSDB_CFG_VTYPE_IPSTR 131 
#define  TSDB_CFG_VTYPE_SHORT 130 
#define  TSDB_CFG_VTYPE_STRING 129 
#define  TSDB_CFG_VTYPE_UINT 128 
 int /*<<< orphan*/  mgmtCheckConfigShow (TYPE_2__*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* tsGlobalConfig ; 
 int tsGlobalConfigNum ; 

int mgmtRetrieveConfigs(SShowObj *pShow, char *data, int rows, SConnObj *pConn) {
  int numOfRows = 0;

  for (int i = tsGlobalConfigNum - 1; i >= 0 && numOfRows < rows; --i) {
    SGlobalConfig *cfg = tsGlobalConfig + i;
    if (!mgmtCheckConfigShow(cfg)) continue;

    char *pWrite;
    int   cols = 0;

    pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
    snprintf(pWrite, TSDB_CFG_OPTION_LEN, "%s", cfg->option);
    cols++;

    pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
    switch (cfg->valType) {
      case TSDB_CFG_VTYPE_SHORT:
        snprintf(pWrite, TSDB_CFG_VALUE_LEN, "%d", *((int16_t *)cfg->ptr));
        numOfRows++;
        break;
      case TSDB_CFG_VTYPE_INT:
        snprintf(pWrite, TSDB_CFG_VALUE_LEN, "%d", *((int32_t *)cfg->ptr));
        numOfRows++;
        break;
      case TSDB_CFG_VTYPE_UINT:
        snprintf(pWrite, TSDB_CFG_VALUE_LEN, "%d", *((uint32_t *)cfg->ptr));
        numOfRows++;
        break;
      case TSDB_CFG_VTYPE_FLOAT:
        snprintf(pWrite, TSDB_CFG_VALUE_LEN, "%f", *((float *)cfg->ptr));
        numOfRows++;
        break;
      case TSDB_CFG_VTYPE_STRING:
      case TSDB_CFG_VTYPE_IPSTR:
      case TSDB_CFG_VTYPE_DIRECTORY:
        snprintf(pWrite, TSDB_CFG_VALUE_LEN, "%s", (char *)cfg->ptr);
        numOfRows++;
        break;
      default:
        break;
    }
  }

  pShow->numOfReads += numOfRows;
  return numOfRows;
}