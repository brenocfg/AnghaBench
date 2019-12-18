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
typedef  int /*<<< orphan*/  TAOS_SUB ;
typedef  int /*<<< orphan*/ * TAOS_ROW ;
typedef  int /*<<< orphan*/  TAOS_FIELD ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/ * taos_consume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * taos_fetch_subfields (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taos_print_row (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int taos_subfields_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * taos_subscribe (char*,char*,char*,char*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  taos_unsubscribe (int /*<<< orphan*/ *) ; 

int main(int argc, char *argv[]) 
{
  TAOS_SUB   *tsub;
  TAOS_ROW    row;
  char        dbname[64], table[64];
  char        temp[256];

  if ( argc == 1 ) {
    printf("usage: %s server-ip db-name table-name \n", argv[0]);
    exit(0);
  } 

  if ( argc >= 2 ) strcpy(dbname, argv[2]);
  if ( argc >= 3 ) strcpy(table, argv[3]);

  tsub = taos_subscribe(argv[1], "root", "taosdata", dbname, table, 0, 1000);
  if ( tsub == NULL ) {
    printf("failed to connet to db:%s\n", dbname);
    exit(1);
  }

  TAOS_FIELD *fields = taos_fetch_subfields(tsub);
  int fcount = taos_subfields_count(tsub);

  printf("start to retrieve data\n");
  printf("please use other taos client, insert rows into %s.%s\n", dbname, table);
  while ( 1 ) {
    row = taos_consume(tsub);
    if ( row == NULL ) break;

    taos_print_row(temp, row, fields, fcount);
    printf("%s\n", temp);
  }

  taos_unsubscribe(tsub);

  return 0;
}