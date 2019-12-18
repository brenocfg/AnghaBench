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
typedef  int int64_t ;
struct TYPE_3__ {int type; int /*<<< orphan*/  bytes; } ;
typedef  int /*<<< orphan*/ ** TAOS_ROW ;
typedef  TYPE_1__ TAOS_FIELD ;

/* Variables and functions */
 size_t MIN (size_t,int /*<<< orphan*/ ) ; 
 char* TSDB_DATA_NULL_STR ; 
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
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 scalar_t__ sprintf (char*,char*,...) ; 
 size_t strlen (int /*<<< orphan*/ *) ; 

int taos_print_row(char *str, TAOS_ROW row, TAOS_FIELD *fields, int num_fields) {
  int len = 0;
  for (int i = 0; i < num_fields; ++i) {
    if (row[i] == NULL) {
      len += sprintf(str + len, "%s ", TSDB_DATA_NULL_STR);
      continue;
    }

    switch (fields[i].type) {
      case TSDB_DATA_TYPE_TINYINT:
        len += sprintf(str + len, "%d ", *((char *)row[i]));
        break;

      case TSDB_DATA_TYPE_SMALLINT:
        len += sprintf(str + len, "%d ", *((short *)row[i]));
        break;

      case TSDB_DATA_TYPE_INT:
        len += sprintf(str + len, "%d ", *((int *)row[i]));
        break;

      case TSDB_DATA_TYPE_BIGINT:
        len += sprintf(str + len, "%lld ", *((int64_t *)row[i]));
        break;

      case TSDB_DATA_TYPE_FLOAT:
        len += sprintf(str + len, "%f ", *((float *)row[i]));
        break;

      case TSDB_DATA_TYPE_DOUBLE:
        len += sprintf(str + len, "%lf ", *((double *)row[i]));
        break;

      case TSDB_DATA_TYPE_BINARY:
      case TSDB_DATA_TYPE_NCHAR: {
        /* limit the max length of string to no greater than the maximum length,
         * in case of not null-terminated string */
        size_t xlen = strlen(row[i]);
        size_t trueLen = MIN(xlen, fields[i].bytes);

        memcpy(str + len, (char*) row[i], trueLen);

        str[len + trueLen] = ' ';
        len += (trueLen + 1);
      }
        break;

      case TSDB_DATA_TYPE_TIMESTAMP:
        len += sprintf(str + len, "%lld ", *((int64_t *)row[i]));
        break;

      case TSDB_DATA_TYPE_BOOL:
        len += sprintf(str + len, "%d ", *((int8_t *)row[i]));
      default:
        break;
    }
  }

  return len;
}