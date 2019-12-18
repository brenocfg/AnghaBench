#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int time_t ;
struct timeval {int tv_sec; int tv_usec; } ;
struct TYPE_4__ {int id; char* name; int timeStamp; int rowsInserted; int rowsRetrieved; int /*<<< orphan*/ * taos; } ;
typedef  int /*<<< orphan*/  TAOS ;
typedef  TYPE_1__ STable ;

/* Variables and functions */
 void* atoi (char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  getchar () ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 
 int numOfTables ; 
 void* points ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,...) ; 
 int st ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ tablesProcessed ; 
 int /*<<< orphan*/  taos_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * taos_connect (char*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taos_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taos_init () ; 
 int /*<<< orphan*/  taos_insert_call_back ; 
 scalar_t__ taos_query (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  taos_query_a (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  taos_select_call_back ; 

int main(int argc, char *argv[])
{
  TAOS   *taos;
  struct  timeval systemTime;
  int     i;
  char    sql[1024]  = { 0 };
  char    prefix[20] = { 0 };
  char    db[128]    = { 0 };
  STable *tableList;

  if (argc != 5) {
    printf("usage: %s server-ip dbname rowsPerTable numOfTables\n", argv[0]);
    exit(0);
  }

  // a simple way to parse input parameters
  if (argc >= 3) strcpy(db, argv[2]);
  if (argc >= 4) points = atoi(argv[3]);
  if (argc >= 5) numOfTables = atoi(argv[4]);

  size_t size = sizeof(STable) * (size_t)numOfTables;
  tableList = (STable *)malloc(size);
  memset(tableList, 0, size);

  taos_init();

  taos = taos_connect(argv[1], "root", "taosdata", NULL, 0);
  if (taos == NULL)
    taos_error(taos);

  printf("success to connect to server\n");

  sprintf(sql, "drop database %s", db);
  taos_query(taos, sql);

  sprintf(sql, "create database %s", db);
  if (taos_query(taos, sql) != 0)
    taos_error(taos);

  sprintf(sql, "use %s", db);
  if (taos_query(taos, sql) != 0)
    taos_error(taos);

  strcpy(prefix, "asytbl_");
  for (i = 0; i < numOfTables; ++i) {
    tableList[i].id = i;
    tableList[i].taos = taos;
    sprintf(tableList[i].name, "%s%d", prefix, i);
    sprintf(sql, "create table %s%d (ts timestamp, volume bigint)", prefix, i);
    if (taos_query(taos, sql) != 0)
      taos_error(taos);
  }  

  gettimeofday(&systemTime, NULL);
  for (i = 0; i < numOfTables; ++i)
    tableList[i].timeStamp = (time_t)(systemTime.tv_sec) * 1000 + systemTime.tv_usec / 1000;

  printf("success to create tables, press any key to insert\n");
  getchar();

  printf("start to insert...\n");
  gettimeofday(&systemTime, NULL);
  st = systemTime.tv_sec * 1000000 + systemTime.tv_usec;

  for (i = 0; i<numOfTables; ++i) {
    // insert records in asynchronous API
    sprintf(sql, "insert into %s values(%ld, 0)", tableList[i].name, 1546300800000 + i);
    taos_query_a(taos, sql, taos_insert_call_back, (void *)(tableList + i));
  }

  printf("once insert finished, presse any key to query\n");
  getchar();

  printf("start to query...\n");
  gettimeofday(&systemTime, NULL);
  st = systemTime.tv_sec * 1000000 + systemTime.tv_usec;
  tablesProcessed = 0;

  for (i = 0; i < numOfTables; ++i) {
    // select records in asynchronous API 
    sprintf(sql, "select * from %s", tableList[i].name);
    taos_query_a(taos, sql, taos_select_call_back, (void *)(tableList + i));
  }

  printf("\nonce finished, press any key to exit\n");
  getchar();

  for (i = 0; i<numOfTables; ++i)  {
    printf("%s inserted:%d retrieved:%d\n", tableList[i].name, tableList[i].rowsInserted, tableList[i].rowsRetrieved);
  }

  getchar();

  taos_close(taos);
  free(tableList);

  printf("==== async demo end====\n");
  printf("\n");
  return 0;
}