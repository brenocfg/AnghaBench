#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* HubDb; } ;
struct TYPE_6__ {int /*<<< orphan*/  AcList; int /*<<< orphan*/  CrlList; int /*<<< orphan*/  RootCertList; } ;
typedef  TYPE_2__ HUB ;
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 int /*<<< orphan*/  CfgGetFolder (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SiLoadAcList (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SiLoadCertList (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SiLoadCrlList (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SiLoadGroupList (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SiLoadUserList (TYPE_2__*,int /*<<< orphan*/ ) ; 

void SiLoadHubDb(HUB *h, FOLDER *f)
{
	// Validate arguments
	if (f == NULL || h == NULL)
	{
		return;
	}

	SiLoadGroupList(h, CfgGetFolder(f, "GroupList"));
	SiLoadUserList(h, CfgGetFolder(f, "UserList"));

	if (h->HubDb != NULL)
	{
		SiLoadCertList(h->HubDb->RootCertList, CfgGetFolder(f, "CertList"));
		SiLoadCrlList(h->HubDb->CrlList, CfgGetFolder(f, "CrlList"));
		SiLoadAcList(h->HubDb->AcList, CfgGetFolder(f, "IPAccessControlList"));
	}
}