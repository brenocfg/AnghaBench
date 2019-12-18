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
struct TYPE_3__ {int /*<<< orphan*/ * pDb; } ;
typedef  int /*<<< orphan*/  SDbObj ;
typedef  TYPE_1__ SConnObj ;

/* Variables and functions */
 int TSDB_CODE_INVALID_DB ; 
 int /*<<< orphan*/ * mgmtGetDb (char*) ; 

int mgmtUseDb(SConnObj *pConn, char *name) {
  SDbObj *pDb;
  int     code = TSDB_CODE_INVALID_DB;

  // here change the default db for connect.
  pDb = mgmtGetDb(name);
  if (pDb) {
    pConn->pDb = pDb;
    code = 0;
  }

  return code;
}