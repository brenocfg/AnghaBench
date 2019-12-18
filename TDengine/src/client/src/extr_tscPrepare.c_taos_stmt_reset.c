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
struct TYPE_3__ {scalar_t__ isInsert; } ;
typedef  int /*<<< orphan*/  TAOS_STMT ;
typedef  TYPE_1__ STscStmt ;

/* Variables and functions */
 int TSDB_CODE_SUCCESS ; 
 int insertStmtReset (TYPE_1__*) ; 

int taos_stmt_reset(TAOS_STMT* stmt) {
  STscStmt* pStmt = (STscStmt*)stmt;
  if (pStmt->isInsert) {
    return insertStmtReset(pStmt);
  }
  return TSDB_CODE_SUCCESS;
}