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
struct TYPE_3__ {char* name; int replica; int days; int keep; int tables; int rows; int cache; int ablocks; int tblocks; int ctime; int clog; int comp; } ;
typedef  TYPE_1__ SDbInfo ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* buffer ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

void taosDumpCreateDbClause(SDbInfo *dbInfo, bool isDumpProperty, FILE *fp) {
  char *pstr = buffer;

  pstr += sprintf(pstr, "CREATE DATABASE IF NOT EXISTS %s", dbInfo->name);
  if (isDumpProperty) {
    pstr += sprintf(pstr,
        " REPLICA %d DAYS %d KEEP %d TABLES %d ROWS %d CACHE %d ABLOCKS %d TBLOCKS %d CTIME %d CLOG %d COMP %d",
        dbInfo->replica, dbInfo->days, dbInfo->keep, dbInfo->tables, dbInfo->rows, dbInfo->cache,
        dbInfo->ablocks, dbInfo->tblocks, dbInfo->ctime, dbInfo->clog, dbInfo->comp);
  }

  fprintf(fp, "%s\n\n", buffer);
}