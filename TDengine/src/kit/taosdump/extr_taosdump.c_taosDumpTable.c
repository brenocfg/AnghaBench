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
struct arguments {int dummy; } ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  STableDef ;
typedef  int /*<<< orphan*/  SColDes ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int TSDB_MAX_COLUMNS ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  taosDumpCreateMTableClause (int /*<<< orphan*/ *,char*,int,struct arguments*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taosDumpCreateTableClause (int /*<<< orphan*/ *,int,struct arguments*,int /*<<< orphan*/ *) ; 
 int taosDumpTableData (int /*<<< orphan*/ *,char*,struct arguments*) ; 
 int taosGetTableDes (char*,int /*<<< orphan*/ *) ; 

int32_t taosDumpTable(char *table, char *metric, struct arguments *arguments, FILE *fp) {
  int count = 0;

  STableDef *tableDes = (STableDef *)calloc(1, sizeof(STableDef) + sizeof(SColDes) * TSDB_MAX_COLUMNS);

  if (metric != NULL && metric[0] != '\0') {  // dump metric definition
    count = taosGetTableDes(metric, tableDes);

    if (count < 0) return -1;

    taosDumpCreateTableClause(tableDes, count, arguments, fp);

    memset(tableDes, 0, sizeof(STableDef) + sizeof(SColDes) * TSDB_MAX_COLUMNS);

    count = taosGetTableDes(table, tableDes);

    if (count < 0) return -1;

    taosDumpCreateMTableClause(tableDes, metric, count, arguments, fp);

  } else {  // dump table definition
    count = taosGetTableDes(table, tableDes);

    if (count < 0) return -1;

    taosDumpCreateTableClause(tableDes, count, arguments, fp);
  }

  return taosDumpTableData(fp, table, arguments);
}