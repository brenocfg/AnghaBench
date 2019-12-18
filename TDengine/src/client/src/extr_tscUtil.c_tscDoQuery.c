#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ command; int isInsertFromFile; } ;
struct TYPE_9__ {void* fp; TYPE_2__ cmd; } ;
typedef  TYPE_1__ SSqlObj ;
typedef  TYPE_2__ SSqlCmd ;

/* Variables and functions */
 scalar_t__ TSDB_SQL_LOCAL ; 
 scalar_t__ TSDB_SQL_SELECT ; 
 int /*<<< orphan*/  tscAddIntoSqlList (TYPE_1__*) ; 
 int /*<<< orphan*/  tscProcessLocalCmd (TYPE_1__*) ; 
 int /*<<< orphan*/  tscProcessMultiVnodesInsert (TYPE_1__*) ; 
 int /*<<< orphan*/  tscProcessMultiVnodesInsertForFile (TYPE_1__*) ; 
 int /*<<< orphan*/  tscProcessSql (TYPE_1__*) ; 

void tscDoQuery(SSqlObj* pSql) {
  SSqlCmd* pCmd = &pSql->cmd;
  void*    fp = pSql->fp;

  if (pCmd->command > TSDB_SQL_LOCAL) {
    tscProcessLocalCmd(pSql);
  } else {
    if (pCmd->command == TSDB_SQL_SELECT) {
      tscAddIntoSqlList(pSql);
    }

    if (pCmd->isInsertFromFile == 1) {
      tscProcessMultiVnodesInsertForFile(pSql);
    } else {
      // pSql may be released in this function if it is a async insertion.
      tscProcessSql(pSql);
      if (NULL == fp) tscProcessMultiVnodesInsert(pSql);
    }
  }
}