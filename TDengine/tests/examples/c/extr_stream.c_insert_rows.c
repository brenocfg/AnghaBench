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
struct TYPE_2__ {char* server_ip; char* db_name; char* tbl_name; } ;
typedef  TYPE_1__ param ;
typedef  int /*<<< orphan*/  TAOS ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ g_thread_exit_flag ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,...) ; 
 int /*<<< orphan*/  taos_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * taos_connect (char*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* taos_errstr (int /*<<< orphan*/ *) ; 
 scalar_t__ taos_query (int /*<<< orphan*/ *,char*) ; 

void* insert_rows(void *sarg)
{
  TAOS  *taos;
  char    command[1024] = { 0 };
  param  *winfo = (param * )sarg;

  if (NULL == winfo){
  	printf("para is null!\n");
    exit(1);
  }

  taos = taos_connect(winfo->server_ip, "root", "taosdata", NULL, 0);
  if (taos == NULL) {
    printf("failed to connet to server:%s\n", winfo->server_ip);
    exit(1);
  }
  
  // drop database
  sprintf(command, "drop database %s;", winfo->db_name);
  if (taos_query(taos, command) != 0) {
    printf("failed to drop database, reason:%s\n", taos_errstr(taos));
    exit(1);
  }

  // create database
  sprintf(command, "create database %s;", winfo->db_name);
  if (taos_query(taos, command) != 0) {
    printf("failed to create database, reason:%s\n", taos_errstr(taos));
    exit(1);
  }

  // use database
  sprintf(command, "use %s;", winfo->db_name);
  if (taos_query(taos, command) != 0) {
    printf("failed to use database, reason:%s\n", taos_errstr(taos));
    exit(1);
  }

  // create table
  sprintf(command, "create table %s (ts timestamp, speed int);", winfo->tbl_name);
  if (taos_query(taos, command) != 0) {
    printf("failed to create table, reason:%s\n", taos_errstr(taos));
    exit(1);
  }

  // insert data
  int index = 0;  
  while (1) {
    if (g_thread_exit_flag) break;
	
    index++;
    sprintf(command, "insert into %s values (%ld, %d)", winfo->tbl_name, 1546300800000+index*1000, index);
    if (taos_query(taos, command)) {
      printf("failed to insert row [%s], reason:%s\n", command, taos_errstr(taos));
    }
    sleep(1);
  }  

  taos_close(taos);
  return 0;
}