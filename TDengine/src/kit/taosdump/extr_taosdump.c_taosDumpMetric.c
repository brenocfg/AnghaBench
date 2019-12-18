#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct arguments {int dummy; } ;
typedef  int int32_t ;
struct TYPE_8__ {int /*<<< orphan*/  metric; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  bytes; } ;
typedef  scalar_t__* TAOS_ROW ;
typedef  TYPE_1__ TAOS_FIELD ;
typedef  TYPE_2__ STableRecord ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRWXU ; 
 int S_IXGRP ; 
 char* command ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int open (char*,int,int) ; 
 scalar_t__ read (int,TYPE_2__*,int) ; 
 int /*<<< orphan*/  remove (char*) ; 
 int /*<<< orphan*/ * result ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taos ; 
 int /*<<< orphan*/  taosDumpTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct arguments*,int /*<<< orphan*/ *) ; 
 TYPE_1__* taos_fetch_fields (int /*<<< orphan*/ *) ; 
 scalar_t__* taos_fetch_row (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taos_free_result (int /*<<< orphan*/ *) ; 
 scalar_t__ taos_query (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * taos_use_result (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tclose (int) ; 
 int /*<<< orphan*/  twrite (int,TYPE_2__*,int) ; 

int32_t taosDumpMetric(char *metric, struct arguments *arguments, FILE *fp) {
  TAOS_ROW row = NULL;
  int fd = -1;
  STableRecord tableRecord;

  strcpy(tableRecord.metric, metric);

  sprintf(command, "select tbname from %s", metric);
  if (taos_query(taos, command) != 0) {
    fprintf(stderr, "failed to run command %s\n", command);
    return -1;
  }

  result = taos_use_result(taos);
  if (result == NULL) {
    fprintf(stderr, "failed to use result\n");
    return -1;
  }

  fd = open(".table.tmp", O_RDWR | O_CREAT, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH);
  if (fd < 0) {
    fprintf(stderr, "failed to open temp file");
    return -1;
  }

  TAOS_FIELD *fields = taos_fetch_fields(result);

  while ((row = taos_fetch_row(result)) != NULL) {
    memset(&tableRecord, 0, sizeof(STableRecord));
    strncpy(tableRecord.name, (char *)row[0], fields[0].bytes);
    strcpy(tableRecord.metric, metric);
    twrite(fd, &tableRecord, sizeof(STableRecord));
  }

  taos_free_result(result);
  result = NULL;

  lseek(fd, 0, SEEK_SET);

  while (read(fd, &tableRecord, sizeof(STableRecord)) > 0) {
    taosDumpTable(tableRecord.name, tableRecord.metric, arguments, fp);
  }

  tclose(fd);
  remove(".table.tmp");

  return 0;
}