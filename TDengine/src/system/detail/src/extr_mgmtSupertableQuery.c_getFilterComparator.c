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
 int TSDB_RELATION_LIKE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * compareDoubleIntVal ; 
 int /*<<< orphan*/ * compareDoubleVal ; 
 int /*<<< orphan*/ * compareIntDoubleVal ; 
 int /*<<< orphan*/ * compareIntVal ; 
 int /*<<< orphan*/ * compareStrPatternComp ; 
 int /*<<< orphan*/ * compareStrVal ; 
 int /*<<< orphan*/ * compareWStrPatternComp ; 
 int /*<<< orphan*/ * compareWStrVal ; 

__attribute__((used)) static __compar_fn_t getFilterComparator(int32_t type, int32_t filterType, int32_t optr) {
  __compar_fn_t comparator = NULL;

  switch (type) {
    case TSDB_DATA_TYPE_TINYINT:
    case TSDB_DATA_TYPE_SMALLINT:
    case TSDB_DATA_TYPE_INT:
    case TSDB_DATA_TYPE_BIGINT:
    case TSDB_DATA_TYPE_BOOL: {
      if (filterType >= TSDB_DATA_TYPE_BOOL && filterType <= TSDB_DATA_TYPE_BIGINT) {
        comparator = compareIntVal;
      } else if (filterType >= TSDB_DATA_TYPE_FLOAT && filterType <= TSDB_DATA_TYPE_DOUBLE) {
        comparator = compareIntDoubleVal;
      }
      break;
    }

    case TSDB_DATA_TYPE_FLOAT:
    case TSDB_DATA_TYPE_DOUBLE: {
      if (filterType >= TSDB_DATA_TYPE_BOOL && filterType <= TSDB_DATA_TYPE_BIGINT) {
        comparator = compareDoubleIntVal;
      } else if (filterType >= TSDB_DATA_TYPE_FLOAT && filterType <= TSDB_DATA_TYPE_DOUBLE) {
        comparator = compareDoubleVal;
      }
      break;
    }

    case TSDB_DATA_TYPE_BINARY: {
      assert(filterType == TSDB_DATA_TYPE_BINARY);

      if (optr == TSDB_RELATION_LIKE) { /* wildcard query using like operator */
        comparator = compareStrPatternComp;
      } else { /* normal relational comparator */
        comparator = compareStrVal;
      }

      break;
    }

    case TSDB_DATA_TYPE_NCHAR: {
      assert(filterType == TSDB_DATA_TYPE_NCHAR);

      if (optr == TSDB_RELATION_LIKE) {
        comparator = compareWStrPatternComp;
      } else {
        comparator = compareWStrVal;
      }

      break;
    }
    default:
      comparator = compareIntVal;
      break;
  }

  return comparator;
}