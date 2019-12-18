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
typedef  void* int64_t ;
typedef  int int32_t ;
typedef  int int16_t ;
struct TYPE_3__ {int iMinVal; int iMaxVal; void* i64MinVal; void* i64MaxVal; double dMinVal; double dMaxVal; } ;
typedef  TYPE_1__ MinMaxEntry ;

/* Variables and functions */
#define  TSDB_DATA_TYPE_BIGINT 133 
#define  TSDB_DATA_TYPE_DOUBLE 132 
#define  TSDB_DATA_TYPE_FLOAT 131 
#define  TSDB_DATA_TYPE_INT 130 
#define  TSDB_DATA_TYPE_SMALLINT 129 
#define  TSDB_DATA_TYPE_TINYINT 128 
 int /*<<< orphan*/  assert (int) ; 

void tMemBucketUpdateBoundingBox(MinMaxEntry *r, char *data, int32_t dataType) {
  switch (dataType) {
    case TSDB_DATA_TYPE_INT: {
      int32_t val = *(int32_t *)data;
      if (r->iMinVal > val) {
        r->iMinVal = val;
      }

      if (r->iMaxVal < val) {
        r->iMaxVal = val;
      }
      break;
    };
    case TSDB_DATA_TYPE_BIGINT: {
      int64_t val = *(int64_t *)data;
      if (r->i64MinVal > val) {
        r->i64MinVal = val;
      }

      if (r->i64MaxVal < val) {
        r->i64MaxVal = val;
      }
      break;
    };
    case TSDB_DATA_TYPE_SMALLINT: {
      int32_t val = *(int16_t *)data;
      if (r->iMinVal > val) {
        r->iMinVal = val;
      }

      if (r->iMaxVal < val) {
        r->iMaxVal = val;
      }
      break;
    };
    case TSDB_DATA_TYPE_TINYINT: {
      int32_t val = *(int8_t *)data;
      if (r->iMinVal > val) {
        r->iMinVal = val;
      }

      if (r->iMaxVal < val) {
        r->iMaxVal = val;
      }

      break;
    };
    case TSDB_DATA_TYPE_DOUBLE: {
      double val = *(double *)data;
      if (r->dMinVal > val) {
        r->dMinVal = val;
      }

      if (r->dMaxVal < val) {
        r->dMaxVal = val;
      }
      break;
    };
    case TSDB_DATA_TYPE_FLOAT: {
      double val = *(float *)data;

      if (r->dMinVal > val) {
        r->dMinVal = val;
      }

      if (r->dMaxVal < val) {
        r->dMaxVal = val;
      }
      break;
    };
    default: { assert(false); }
  }
}