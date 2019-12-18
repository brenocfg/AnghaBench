#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  user; scalar_t__ acctId; } ;
typedef  TYPE_1__ SAcctObj ;

/* Variables and functions */
 TYPE_1__ acctObj ; 
 int /*<<< orphan*/  mgmtCreateUser (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 char* tsInternalPass ; 

void mgmtCheckAcct() {
  SAcctObj *pAcct = &acctObj;
  pAcct->acctId = 0;
  strcpy(pAcct->user, "root");

  mgmtCreateUser(pAcct, "root", "taosdata");
  mgmtCreateUser(pAcct, "monitor", tsInternalPass);
  mgmtCreateUser(pAcct, "_root", tsInternalPass);
}