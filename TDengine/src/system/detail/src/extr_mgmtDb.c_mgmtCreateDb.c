#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  user; } ;
struct TYPE_13__ {scalar_t__ daysToKeep1; scalar_t__ daysToKeep2; scalar_t__ daysToKeep; int /*<<< orphan*/  acct; int /*<<< orphan*/  db; } ;
struct TYPE_12__ {TYPE_2__ cfg; int /*<<< orphan*/  createdTime; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ SDbObj ;
typedef  TYPE_2__ SCreateDbMsg ;
typedef  TYPE_3__ SAcctObj ;

/* Variables and functions */
 int TSDB_CODE_DB_ALREADY_EXIST ; 
 int TSDB_CODE_SDB_ERROR ; 
 int TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dbSdb ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int mgmtCheckDbGrant () ; 
 int mgmtCheckDbLimit (TYPE_3__*) ; 
 int mgmtCheckDbParams (TYPE_2__*) ; 
 scalar_t__ sdbGetRow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sdbInsertRow (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosGetTimestampMs () ; 
 int /*<<< orphan*/  tfree (TYPE_1__*) ; 

int mgmtCreateDb(SAcctObj *pAcct, SCreateDbMsg *pCreate) {
  SDbObj *pDb;
  int code;

  code = mgmtCheckDbLimit(pAcct);
  if (code != 0) {
    return code;
  }

  pDb = (SDbObj *)sdbGetRow(dbSdb, pCreate->db);
  if (pDb != NULL) {
    return TSDB_CODE_DB_ALREADY_EXIST;
  }

  code = mgmtCheckDbParams(pCreate);
  if (code != TSDB_CODE_SUCCESS) return code;

  assert(pCreate->daysToKeep1 <= pCreate->daysToKeep2 && pCreate->daysToKeep2 <= pCreate->daysToKeep);

  code = mgmtCheckDbGrant();
  if (code != 0) {
    return code;
  }

  pDb = malloc(sizeof(SDbObj));
  memset(pDb, 0, sizeof(SDbObj));
  strcpy(pDb->name, pCreate->db);
  strcpy(pCreate->acct, pAcct->user);
  pDb->createdTime = taosGetTimestampMs();
  pDb->cfg = *pCreate;

  if (sdbInsertRow(dbSdb, pDb, 0) < 0) {
    code = TSDB_CODE_SDB_ERROR;
    tfree(pDb);
  }

  return code;
}