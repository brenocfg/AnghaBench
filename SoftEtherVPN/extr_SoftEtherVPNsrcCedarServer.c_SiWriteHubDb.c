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
struct TYPE_3__ {int /*<<< orphan*/  AcList; int /*<<< orphan*/  CrlList; int /*<<< orphan*/  RootCertList; int /*<<< orphan*/  GroupList; int /*<<< orphan*/  UserList; } ;
typedef  TYPE_1__ HUBDB ;
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 int /*<<< orphan*/  CfgCreateFolder (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SiWriteAcList (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SiWriteCertList (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SiWriteCrlList (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SiWriteGroupList (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SiWriteUserList (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void SiWriteHubDb(FOLDER *f, HUBDB *db, bool no_save_ac_list)
{
	// Validate arguments
	if (f == NULL || db == NULL)
	{
		return;
	}

	SiWriteUserList(CfgCreateFolder(f, "UserList"), db->UserList);
	SiWriteGroupList(CfgCreateFolder(f, "GroupList"), db->GroupList);
	SiWriteCertList(CfgCreateFolder(f, "CertList"), db->RootCertList);
	SiWriteCrlList(CfgCreateFolder(f, "CrlList"), db->CrlList);

	if (no_save_ac_list == false)
	{
		SiWriteAcList(CfgCreateFolder(f, "IPAccessControlList"), db->AcList);
	}
}