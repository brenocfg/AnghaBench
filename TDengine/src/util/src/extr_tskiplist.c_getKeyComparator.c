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
typedef  int /*<<< orphan*/ * __compar_fn_t ;

/* Variables and functions */
#define  TSDB_DATA_TYPE_BIGINT 136 
#define  TSDB_DATA_TYPE_BINARY 135 
#define  TSDB_DATA_TYPE_BOOL 134 
#define  TSDB_DATA_TYPE_DOUBLE 133 
#define  TSDB_DATA_TYPE_FLOAT 132 
#define  TSDB_DATA_TYPE_INT 131 
#define  TSDB_DATA_TYPE_NCHAR 130 
#define  TSDB_DATA_TYPE_SMALLINT 129 
#define  TSDB_DATA_TYPE_TINYINT 128 
 int /*<<< orphan*/ * compareDoubleVal ; 
 int /*<<< orphan*/ * compareIntVal ; 
 int /*<<< orphan*/ * compareStrVal ; 
 int /*<<< orphan*/ * compareWStrVal ; 

__attribute__((used)) static __compar_fn_t getKeyComparator(int32_t keyType) {
  __compar_fn_t comparator = NULL;

  switch (keyType) {
    case TSDB_DATA_TYPE_TINYINT:
    case TSDB_DATA_TYPE_SMALLINT:
    case TSDB_DATA_TYPE_INT:
    case TSDB_DATA_TYPE_BIGINT:
    case TSDB_DATA_TYPE_BOOL:
      comparator = compareIntVal;
      break;

    case TSDB_DATA_TYPE_FLOAT:
    case TSDB_DATA_TYPE_DOUBLE:
      comparator = compareDoubleVal;
      break;

    case TSDB_DATA_TYPE_BINARY:
      comparator = compareStrVal;
      break;

    case TSDB_DATA_TYPE_NCHAR:
      comparator = compareWStrVal;
      break;

    default:
      comparator = compareIntVal;
      break;
  }

  return comparator;
}