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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_COMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_DOUBLE_VAL (char*) ; 
 int /*<<< orphan*/  GET_FLOAT_VAL (char*) ; 
 int /*<<< orphan*/  GET_INT16_VAL (char*) ; 
 int /*<<< orphan*/  GET_INT32_VAL (char*) ; 
 int /*<<< orphan*/  GET_INT64_VAL (char*) ; 
 int /*<<< orphan*/  GET_INT8_VAL (char*) ; 
#define  TSDB_DATA_TYPE_BIGINT 135 
#define  TSDB_DATA_TYPE_BOOL 134 
#define  TSDB_DATA_TYPE_DOUBLE 133 
#define  TSDB_DATA_TYPE_FLOAT 132 
#define  TSDB_DATA_TYPE_INT 131 
#define  TSDB_DATA_TYPE_NCHAR 130 
#define  TSDB_DATA_TYPE_SMALLINT 129 
#define  TSDB_DATA_TYPE_TINYINT 128 
 int TSDB_NCHAR_SIZE ; 
 int strncmp (char*,char*,size_t) ; 
 int wcsncmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int32_t doCompare(char* f1, char* f2, int32_t type, int32_t size) {
  switch (type) {
    case TSDB_DATA_TYPE_INT:        DEFAULT_COMP(GET_INT32_VAL(f1), GET_INT32_VAL(f2));
    case TSDB_DATA_TYPE_DOUBLE:     DEFAULT_COMP(GET_DOUBLE_VAL(f1), GET_DOUBLE_VAL(f2));
    case TSDB_DATA_TYPE_FLOAT:      DEFAULT_COMP(GET_FLOAT_VAL(f1), GET_FLOAT_VAL(f2));
    case TSDB_DATA_TYPE_BIGINT:     DEFAULT_COMP(GET_INT64_VAL(f1), GET_INT64_VAL(f2));
    case TSDB_DATA_TYPE_SMALLINT:   DEFAULT_COMP(GET_INT16_VAL(f1), GET_INT16_VAL(f2));
    case TSDB_DATA_TYPE_TINYINT:
    case TSDB_DATA_TYPE_BOOL:       DEFAULT_COMP(GET_INT8_VAL(f1), GET_INT8_VAL(f2));
    case TSDB_DATA_TYPE_NCHAR: {
      int32_t ret = wcsncmp((wchar_t*) f1, (wchar_t*) f2, size/TSDB_NCHAR_SIZE);
      if (ret == 0) {
          return ret;
      }
      return (ret < 0) ? -1 : 1;
    }
    default: {
      int32_t ret = strncmp(f1, f2, (size_t)size);
      if (ret == 0) {
        return ret;
      }

      return (ret < 0) ? -1 : 1;
    }
  }
}