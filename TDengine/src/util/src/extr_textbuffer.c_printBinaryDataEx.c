#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int int8_t ;
typedef  double int64_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int int16_t ;
struct TYPE_3__ {scalar_t__ functionId; int type; } ;
typedef  TYPE_1__ SSrcColumnInfo ;

/* Variables and functions */
#define  TSDB_DATA_TYPE_BIGINT 135 
#define  TSDB_DATA_TYPE_BINARY 134 
#define  TSDB_DATA_TYPE_DOUBLE 133 
#define  TSDB_DATA_TYPE_FLOAT 132 
#define  TSDB_DATA_TYPE_INT 131 
#define  TSDB_DATA_TYPE_SMALLINT 130 
#define  TSDB_DATA_TYPE_TIMESTAMP 129 
#define  TSDB_DATA_TYPE_TINYINT 128 
 scalar_t__ TSDB_FUNC_AVG ; 
 scalar_t__ TSDB_FUNC_LAST_DST ; 
 int /*<<< orphan*/  TSDB_KEYSIZE ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void printBinaryDataEx(char *data, int32_t len, SSrcColumnInfo *param) {
  if (param->functionId == TSDB_FUNC_LAST_DST) {
    switch (param->type) {
      case TSDB_DATA_TYPE_TINYINT:printf("%lld,%d\t", *(int64_t *) data, *(int8_t *) (data + TSDB_KEYSIZE + 1));
        break;
      case TSDB_DATA_TYPE_SMALLINT:printf("%lld,%d\t", *(int64_t *) data, *(int16_t *) (data + TSDB_KEYSIZE + 1));
        break;
      case TSDB_DATA_TYPE_TIMESTAMP:
      case TSDB_DATA_TYPE_BIGINT:printf("%lld,%lld\t", *(int64_t *) data, *(int64_t *) (data + TSDB_KEYSIZE + 1));
        break;
      case TSDB_DATA_TYPE_FLOAT:printf("%lld,%d\t", *(int64_t *) data, *(float *) (data + TSDB_KEYSIZE + 1));
        break;
      case TSDB_DATA_TYPE_DOUBLE:printf("%lld,%d\t", *(int64_t *) data, *(double *) (data + TSDB_KEYSIZE + 1));
        break;
      case TSDB_DATA_TYPE_BINARY:printf("%lld,%s\t", *(int64_t *) data, (data + TSDB_KEYSIZE + 1));
        break;

      case TSDB_DATA_TYPE_INT:
      default:printf("%lld,%d\t", *(int64_t *) data, *(int32_t *) (data + TSDB_KEYSIZE + 1));
        break;
    }
  } else if (param->functionId == TSDB_FUNC_AVG) {
      printf("%f,%lld\t", *(double *) data, *(int64_t *) (data + sizeof(double) + 1));
  } else {
    // functionId == TSDB_FUNC_MAX_DST | TSDB_FUNC_TAG
    switch (param->type) {
      case TSDB_DATA_TYPE_TINYINT:
        printf("%d\t", *(int8_t *)data);
        break;
      case TSDB_DATA_TYPE_SMALLINT:
        printf("%d\t", *(int16_t *)data);
        break;
      case TSDB_DATA_TYPE_TIMESTAMP:
      case TSDB_DATA_TYPE_BIGINT:
        printf("%lld\t", *(int64_t *)data);
        break;
      case TSDB_DATA_TYPE_FLOAT:
        printf("%d\t", *(float *)data);
        break;
      case TSDB_DATA_TYPE_DOUBLE:
        printf("%d\t", *(double *)data);
        break;
      case TSDB_DATA_TYPE_BINARY:
        printf("%s\t", data);
        break;

      case TSDB_DATA_TYPE_INT:
      default:
        printf("%d\t", *(double *)data);
        break;
    }
  }
}