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
 int /*<<< orphan*/ * filterFunc_dd ; 
 int /*<<< orphan*/ * filterFunc_ds ; 
 int /*<<< orphan*/ * filterFunc_i16 ; 
 int /*<<< orphan*/ * filterFunc_i32 ; 
 int /*<<< orphan*/ * filterFunc_i64 ; 
 int /*<<< orphan*/ * filterFunc_i8 ; 
 int /*<<< orphan*/ * filterFunc_nchar ; 
 int /*<<< orphan*/ * filterFunc_str ; 

__filter_func_t* vnodeGetValueFilterFuncArray(int32_t type) {
  switch(type) {
    case TSDB_DATA_TYPE_BOOL:       return filterFunc_i8;
    case TSDB_DATA_TYPE_TINYINT:    return filterFunc_i8;
    case TSDB_DATA_TYPE_SMALLINT:   return filterFunc_i16;
    case TSDB_DATA_TYPE_INT:        return filterFunc_i32;
    case TSDB_DATA_TYPE_TIMESTAMP:  //timestamp uses bigint filter
    case TSDB_DATA_TYPE_BIGINT:     return filterFunc_i64;
    case TSDB_DATA_TYPE_FLOAT:      return filterFunc_ds;
    case TSDB_DATA_TYPE_DOUBLE:     return filterFunc_dd;
    case TSDB_DATA_TYPE_BINARY:     return filterFunc_str;
    case TSDB_DATA_TYPE_NCHAR:      return filterFunc_nchar;
    default: return NULL;
  }
}