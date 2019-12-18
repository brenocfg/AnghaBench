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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_10__ {char* user; } ;
struct TYPE_9__ {char* user; char* acct; int superAuth; int writeAuth; int /*<<< orphan*/  createdTime; int /*<<< orphan*/  pass; } ;
typedef  TYPE_1__ SUserObj ;
typedef  TYPE_2__ SAcctObj ;

/* Variables and functions */
 int TSDB_CODE_SDB_ERROR ; 
 int TSDB_CODE_SUCCESS ; 
 int TSDB_CODE_USER_ALREADY_EXIST ; 
 int /*<<< orphan*/  mWarn (char*,char*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int mgmtCheckUserGrant () ; 
 int mgmtCheckUserLimit (TYPE_2__*) ; 
 scalar_t__ sdbGetRow (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ sdbInsertRow (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  taosEncryptPass (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosGetTimestampMs () ; 
 int /*<<< orphan*/  tfree (TYPE_1__*) ; 
 int /*<<< orphan*/  userSdb ; 

int mgmtCreateUser(SAcctObj *pAcct, char *name, char *pass) {
  SUserObj *pUser;
  int code;

  code = mgmtCheckUserLimit(pAcct);
  if (code != 0) {
    return code;
  }

  pUser = (SUserObj *)sdbGetRow(userSdb, name);
  if (pUser != NULL) {
    mWarn("user:%s is already there", name);
    return TSDB_CODE_USER_ALREADY_EXIST;
  }

  code = mgmtCheckUserGrant();
  if (code != 0) {
    return code;
  }

  pUser = malloc(sizeof(SUserObj));
  memset(pUser, 0, sizeof(SUserObj));
  strcpy(pUser->user, name);
  taosEncryptPass((uint8_t*) pass, strlen(pass), pUser->pass);
  strcpy(pUser->acct, pAcct->user);
  pUser->createdTime = taosGetTimestampMs();
  pUser->superAuth = 0;
  pUser->writeAuth = 1;
  if (strcmp(pUser->user, "root") == 0 || strcmp(pUser->user, pUser->acct) == 0) {
    pUser->superAuth = 1;
  }

  code = TSDB_CODE_SUCCESS;
  if (sdbInsertRow(userSdb, pUser, 0) < 0) {
    tfree(pUser);
    code = TSDB_CODE_SDB_ERROR;
  }

  //  mgmtAddUserIntoAcct(pAcct, pUser);

  return code;
}