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
typedef  int /*<<< orphan*/  TAOS_ROW ;
typedef  int /*<<< orphan*/  TAOS_RES ;
typedef  int /*<<< orphan*/  TAOS_FIELD ;
typedef  int /*<<< orphan*/  TAOS ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int getchar () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/ * taos_connect (char*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* taos_errstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * taos_fetch_fields (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taos_fetch_row (int /*<<< orphan*/ *) ; 
 int taos_field_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taos_free_result (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taos_init () ; 
 int /*<<< orphan*/  taos_print_row (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ taos_query (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * taos_use_result (int /*<<< orphan*/ *) ; 

int main(int argc, char *argv[]) {
  TAOS *    taos;
  char      qstr[1024];
  TAOS_RES *result;

  // connect to server
  if (argc < 2) {
    printf("please input server-ip \n");
    return 0;
  }

  // init TAOS
  taos_init();

  taos = taos_connect(argv[1], "root", "taosdata", NULL, 0);
  if (taos == NULL) {
    printf("failed to connect to server, reason:%s\n", taos_errstr(taos));
    exit(1);
  }
  printf("success to connect to server\n");
  

  taos_query(taos, "drop database demo");
  if (taos_query(taos, "create database demo") != 0) {
    printf("failed to create database, reason:%s\n", taos_errstr(taos));
    exit(1);
  }
  printf("success to create database\n");

  taos_query(taos, "use demo");

  // create table
  if (taos_query(taos, "create table m1 (ts timestamp, speed int)") != 0) {
    printf("failed to create table, reason:%s\n", taos_errstr(taos));
    exit(1);
  }
  printf("success to create table\n");

  // sleep for one second to make sure table is created on data node
  // taosMsleep(1000);

  // insert 10 records
  int i = 0;
  for (i = 0; i < 10; ++i) {
    sprintf(qstr, "insert into m1 values (%ld, %d)", 1546300800000 + i * 1000, i * 10);
    if (taos_query(taos, qstr)) {
      printf("failed to insert row: %i, reason:%s\n", i, taos_errstr(taos));
    }
    //sleep(1);
  }
  printf("success to insert rows, total %d rows\n", i);

  // query the records
  sprintf(qstr, "SELECT * FROM m1");
  if (taos_query(taos, qstr) != 0) {
    printf("failed to select, reason:%s\n", taos_errstr(taos));
    exit(1);
  }

  result = taos_use_result(taos);

  if (result == NULL) {
    printf("failed to get result, reason:%s\n", taos_errstr(taos));
    exit(1);
  }

  TAOS_ROW    row;
  int         rows = 0;
  int         num_fields = taos_field_count(taos);
  TAOS_FIELD *fields = taos_fetch_fields(result);
  char        temp[256];

  printf("select * from table, result:\n");
  // fetch the records row by row
  while ((row = taos_fetch_row(result))) {
    rows++;
    taos_print_row(temp, row, fields, num_fields);
    printf("%s\n", temp);
  }

  taos_free_result(result);
  printf("====demo end====\n\n");
  return getchar();
}