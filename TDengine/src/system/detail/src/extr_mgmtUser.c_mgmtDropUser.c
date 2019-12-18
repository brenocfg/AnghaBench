#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  user; } ;
struct TYPE_5__ {int /*<<< orphan*/  acct; } ;
typedef  TYPE_1__ SUserObj ;
typedef  TYPE_2__ SAcctObj ;

/* Variables and functions */
 int TSDB_CODE_INVALID_USER ; 
 int TSDB_CODE_NO_RIGHTS ; 
 int /*<<< orphan*/  mWarn (char*,char*) ; 
 int /*<<< orphan*/  sdbDeleteRow (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ sdbGetRow (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  userSdb ; 

int mgmtDropUser(SAcctObj *pAcct, char *name) {
  SUserObj *pUser;

  pUser = (SUserObj *)sdbGetRow(userSdb, name);
  if (pUser == NULL) {
    mWarn("user:%s is not there", name);
    return TSDB_CODE_INVALID_USER;
  }

  if (strcmp(pAcct->user, pUser->acct) != 0) return TSDB_CODE_NO_RIGHTS;

  //  mgmtRemoveUserFromAcct(pAcct, pUser);
  sdbDeleteRow(userSdb, pUser);

  return 0;
}