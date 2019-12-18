#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* cols; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  bytes; } ;
struct TYPE_6__ {int length; int /*<<< orphan*/  note; int /*<<< orphan*/  type; int /*<<< orphan*/  field; } ;
typedef  scalar_t__* TAOS_ROW ;
typedef  TYPE_2__ TAOS_FIELD ;
typedef  TYPE_3__ STableDef ;

/* Variables and functions */
 size_t TSDB_DESCRIBE_METRIC_FIELD_INDEX ; 
 size_t TSDB_DESCRIBE_METRIC_LENGTH_INDEX ; 
 size_t TSDB_DESCRIBE_METRIC_NOTE_INDEX ; 
 size_t TSDB_DESCRIBE_METRIC_TYPE_INDEX ; 
 char* command ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * result ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taos ; 
 TYPE_2__* taos_fetch_fields (int /*<<< orphan*/ *) ; 
 scalar_t__* taos_fetch_row (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taos_free_result (int /*<<< orphan*/ *) ; 
 scalar_t__ taos_query (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * taos_use_result (int /*<<< orphan*/ ) ; 

int taosGetTableDes(char *table, STableDef *tableDes) {
  TAOS_ROW row = NULL;
  int count = 0;

  sprintf(command, "describe %s", table);
  if (taos_query(taos, command) != 0) {
    fprintf(stderr, "failed to run command %s\n", command);
    return -1;
  }

  result = taos_use_result(taos);
  if (result == NULL) {
    fprintf(stderr, "failed to use result\n");
    return -1;
  }

  TAOS_FIELD *fields = taos_fetch_fields(result);

  strcpy(tableDes->name, table);

  while ((row = taos_fetch_row(result)) != NULL) {
    strncpy(tableDes->cols[count].field, (char *)row[TSDB_DESCRIBE_METRIC_FIELD_INDEX],
            fields[TSDB_DESCRIBE_METRIC_FIELD_INDEX].bytes);
    strncpy(tableDes->cols[count].type, (char *)row[TSDB_DESCRIBE_METRIC_TYPE_INDEX],
            fields[TSDB_DESCRIBE_METRIC_TYPE_INDEX].bytes);
    tableDes->cols[count].length = *((int *)row[TSDB_DESCRIBE_METRIC_LENGTH_INDEX]);
    strncpy(tableDes->cols[count].note, (char *)row[TSDB_DESCRIBE_METRIC_NOTE_INDEX],
            fields[TSDB_DESCRIBE_METRIC_NOTE_INDEX].bytes);

    count++;
  }

  taos_free_result(result);
  result = NULL;

  return count;
}