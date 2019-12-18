#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ numOfCols; TYPE_1__* pFields; } ;
typedef  TYPE_2__ tColModel ;
typedef  int int8_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  scalar_t__ int32_t ;
typedef  int int16_t ;
struct TYPE_5__ {int type; int /*<<< orphan*/  bytes; } ;

/* Variables and functions */
 char* COLMODEL_GET_VAL (char*,TYPE_2__*,scalar_t__,scalar_t__,scalar_t__) ; 
#define  TSDB_DATA_TYPE_BIGINT 137 
#define  TSDB_DATA_TYPE_BINARY 136 
#define  TSDB_DATA_TYPE_BOOL 135 
#define  TSDB_DATA_TYPE_DOUBLE 134 
#define  TSDB_DATA_TYPE_FLOAT 133 
#define  TSDB_DATA_TYPE_INT 132 
#define  TSDB_DATA_TYPE_NCHAR 131 
#define  TSDB_DATA_TYPE_SMALLINT 130 
#define  TSDB_DATA_TYPE_TIMESTAMP 129 
#define  TSDB_DATA_TYPE_TINYINT 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  printBinaryData (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  taosUcs4ToMbs (char*,int /*<<< orphan*/ ,char*) ; 

void tColModelDisplay(tColModel *pModel, void *pData, int32_t numOfRows, int32_t totalCapacity) {
  for (int32_t i = 0; i < numOfRows; ++i) {
    for (int32_t j = 0; j < pModel->numOfCols; ++j) {
      char *val = COLMODEL_GET_VAL((char *)pData, pModel, totalCapacity, i, j);

      int type = pModel->pFields[j].type;
      printf("type:%d ", type);

      switch (type) {
        case TSDB_DATA_TYPE_BIGINT:
          printf("%lld\t", *(int64_t *)val);
          break;
        case TSDB_DATA_TYPE_INT:
          printf("%d\t", *(int32_t *)val);
          break;
        case TSDB_DATA_TYPE_NCHAR: {
          char buf[4096] = {0};
          taosUcs4ToMbs(val, pModel->pFields[j].bytes, buf);
          printf("%s\t", buf);
        }
        case TSDB_DATA_TYPE_BINARY: {
          printBinaryData(val, pModel->pFields[j].bytes);
          break;
        }
        case TSDB_DATA_TYPE_DOUBLE:
          printf("%lf\t", *(double *)val);
          break;
        case TSDB_DATA_TYPE_TIMESTAMP:
          printf("%lld\t", *(int64_t *)val);
          break;
        case TSDB_DATA_TYPE_TINYINT:
          printf("%d\t", *(int8_t *)val);
          break;
        case TSDB_DATA_TYPE_SMALLINT:
          printf("%d\t", *(int16_t *)val);
          break;
        case TSDB_DATA_TYPE_BOOL:
          printf("%d\t", *(int8_t *)val);
          break;
        case TSDB_DATA_TYPE_FLOAT:
          printf("%f\t", *(float *)val);
          break;
        default:
          assert(false);
      }
    }
    printf("\n");
  }
  printf("\n");
}