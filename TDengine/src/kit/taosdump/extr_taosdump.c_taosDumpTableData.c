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
struct arguments {int data_batch; int /*<<< orphan*/  end_time; int /*<<< orphan*/  start_time; scalar_t__ schemaonly; } ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_3__ {int type; int /*<<< orphan*/  bytes; } ;
typedef  int /*<<< orphan*/ ** TAOS_ROW ;
typedef  TYPE_1__ TAOS_FIELD ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND_SIZE ; 
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
 char* buffer ; 
 char* command ; 
 int /*<<< orphan*/  converStringToReadable (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convertNCharToReadable (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * result ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/ * stderr ; 
 char* stpcpy (char*,char*) ; 
 int /*<<< orphan*/  taos ; 
 char* taos_errstr (int /*<<< orphan*/ ) ; 
 TYPE_1__* taos_fetch_fields (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** taos_fetch_row (int /*<<< orphan*/ *) ; 
 int taos_field_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taos_free_result (int /*<<< orphan*/ *) ; 
 scalar_t__ taos_query (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * taos_use_result (int /*<<< orphan*/ ) ; 

int taosDumpTableData(FILE *fp, char *tbname, struct arguments *arguments) {
  /* char       temp[MAX_COMMAND_SIZE] = "\0"; */
  int count = 0;
  char *pstr = NULL;
  TAOS_ROW row = NULL;
  int numFields = 0;
  char *tbuf = NULL;

  if (arguments->schemaonly) return 0;

  sprintf(command, "select * from %s where _c0 >= %ld and _c0 <= %ld order by _c0 asc", tbname, arguments->start_time,
          arguments->end_time);
  if (taos_query(taos, command) != 0) {
    fprintf(stderr, "failed to run command %s, reason: %s\n", command, taos_errstr(taos));
    return -1;
  }

  result = taos_use_result(taos);
  if (result == NULL) {
    fprintf(stderr, "failed to use result\n");
    return -1;
  }

  numFields = taos_field_count(taos);
  assert(numFields > 0);
  TAOS_FIELD *fields = taos_fetch_fields(result);
  tbuf = (char *)malloc(COMMAND_SIZE);
  if (tbuf == NULL) {
    fprintf(stderr, "No enough memory\n");
    return -1;
  }

  count = 0;
  while ((row = taos_fetch_row(result)) != NULL) {
    pstr = buffer;

    if (count == 0) {
      pstr += sprintf(pstr, "INSERT INTO %s VALUES (", tbname);
    } else {
      pstr += sprintf(pstr, "(");
    }

    for (int col = 0; col < numFields; col++) {
      if (col != 0) pstr += sprintf(pstr, ", ");

      if (row[col] == NULL) {
        pstr += sprintf(pstr, "NULL");
        continue;
      }

      switch (fields[col].type) {
        case TSDB_DATA_TYPE_BOOL:
          pstr += sprintf(pstr, "%d", ((((int)(*((char *)row[col]))) == 1) ? 1 : 0));
          break;
        case TSDB_DATA_TYPE_TINYINT:
          pstr += sprintf(pstr, "%d", (int)(*((char *)row[col])));
          break;
        case TSDB_DATA_TYPE_SMALLINT:
          pstr += sprintf(pstr, "%d", (int)(*((short *)row[col])));
          break;
        case TSDB_DATA_TYPE_INT:
          pstr += sprintf(pstr, "%d", *((int *)row[col]));
          break;
        case TSDB_DATA_TYPE_BIGINT:
          pstr += sprintf(pstr, "%ld", *((int64_t *)row[col]));
          break;
        case TSDB_DATA_TYPE_FLOAT:
          pstr += sprintf(pstr, "%f", *((float *)row[col]));
          break;
        case TSDB_DATA_TYPE_DOUBLE:
          pstr += sprintf(pstr, "%f", *((double *)row[col]));
          break;
        case TSDB_DATA_TYPE_BINARY:
          *(pstr++) = '\'';
          converStringToReadable((char *)row[col], fields[col].bytes, tbuf, COMMAND_SIZE);
          pstr = stpcpy(pstr, tbuf);
          *(pstr++) = '\'';
          break;
        case TSDB_DATA_TYPE_NCHAR:
          convertNCharToReadable((char *)row[col], fields[col].bytes, tbuf, COMMAND_SIZE);
          pstr += sprintf(pstr, "\'%s\'", tbuf);
          break;
        case TSDB_DATA_TYPE_TIMESTAMP:
          pstr += sprintf(pstr, "%ld", *(int64_t *)row[col]);
          break;
        default:
          break;
      }
    }
    pstr += sprintf(pstr, ")");

    count++;
    fprintf(fp, "%s", buffer);

    if (count >= arguments->data_batch) {
      fprintf(fp, "\n");
      count = 0;
    } else {
      fprintf(fp, "\\\n");
    }
  }

  fprintf(fp, "\n");

  if (tbuf) free(tbuf);
  taos_free_result(result);
  result = NULL;
  return 0;
}