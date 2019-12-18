#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int int32_t ;
typedef  int /*<<< orphan*/  __filter_func_t ;

/* Variables and functions */
#define  TSDB_DATA_TYPE_BIGINT 135 
#define  TSDB_DATA_TYPE_BOOL 134 
#define  TSDB_DATA_TYPE_DOUBLE 133 
#define  TSDB_DATA_TYPE_FLOAT 132 
#define  TSDB_DATA_TYPE_INT 131 
#define  TSDB_DATA_TYPE_SMALLINT 130 
#define  TSDB_DATA_TYPE_TIMESTAMP 129 
#define  TSDB_DATA_TYPE_TINYINT 128 
 int /*<<< orphan*/ * rangeFilterFunc_dd ; 
 int /*<<< orphan*/ * rangeFilterFunc_ds ; 
 int /*<<< orphan*/ * rangeFilterFunc_i16 ; 
 int /*<<< orphan*/ * rangeFilterFunc_i32 ; 
 int /*<<< orphan*/ * rangeFilterFunc_i64 ; 
 int /*<<< orphan*/ * rangeFilterFunc_i8 ; 

__filter_func_t* vnodeGetRangeFilterFuncArray(int32_t type) {
  switch(type) {
    case TSDB_DATA_TYPE_BOOL:       return rangeFilterFunc_i8;
    case TSDB_DATA_TYPE_TINYINT:    return rangeFilterFunc_i8;
    case TSDB_DATA_TYPE_SMALLINT:   return rangeFilterFunc_i16;
    case TSDB_DATA_TYPE_INT:        return rangeFilterFunc_i32;
    case TSDB_DATA_TYPE_TIMESTAMP:  //timestamp uses bigint filter
    case TSDB_DATA_TYPE_BIGINT:     return rangeFilterFunc_i64;
    case TSDB_DATA_TYPE_FLOAT:      return rangeFilterFunc_ds;
    case TSDB_DATA_TYPE_DOUBLE:     return rangeFilterFunc_dd;
    default:return NULL;
  }
}