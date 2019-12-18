#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_2__ {char* sql; } ;
typedef  int /*<<< orphan*/  TAOS_ROW ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_1__ arguments ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ getTimeStampMs () ; 
 int /*<<< orphan*/  getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int strlen (char*) ; 
 void* taos_connect (char*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taos_error (void*) ; 
 char* taos_errstr (void*) ; 
 int /*<<< orphan*/  taos_fetch_row (void*) ; 
 int /*<<< orphan*/  taos_free_result (void*) ; 
 int taos_query (void*,char*) ; 
 void* taos_use_result (void*) ; 

void readData() {
  printf("read data\n");
  printf("---- sql: %s\n", arguments.sql);

  void *taos = taos_connect("127.0.0.1", "root", "taosdata", NULL, 0);
  if (taos == NULL)
    taos_error(taos);

  FILE *fp = fopen(arguments.sql, "r");
  if (fp == NULL) {
    printf("failed to open file %s\n", arguments.sql);
    exit(1);
  }
  printf("open file %s success\n", arguments.sql);

  char *line = NULL;
  size_t len = 0;
  while (!feof(fp)) {
    free(line);
    line = NULL;
    len = 0;

    getline(&line, &len, fp);
    if (line == NULL) break;

    if (strlen(line) < 10) continue;

    int64_t st = getTimeStampMs();

    int code = taos_query(taos, line);
    if (code != 0) {
      taos_error(taos);
    }

    void *result = taos_use_result(taos);
    if (result == NULL) {
      printf("failed to get result, reason:%s\n", taos_errstr(taos));
      exit(1);
    }

    TAOS_ROW row;
    int rows = 0;
    //int num_fields = taos_field_count(taos);
    //TAOS_FIELD *fields = taos_fetch_fields(result);
    while ((row = taos_fetch_row(result))) {
      rows++;
      //char        temp[256];
      //taos_print_row(temp, row, fields, num_fields);
      //printf("%s\n", temp);
    }

    taos_free_result(result);

    int64_t elapsed = getTimeStampMs() - st;
    float seconds = (float)elapsed / 1000;
    printf("---- Spent %f seconds to query: %s", seconds, line);
  }

  fclose(fp);
}