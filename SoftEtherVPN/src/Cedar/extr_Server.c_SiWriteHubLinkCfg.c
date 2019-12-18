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
struct TYPE_3__ {int CheckServerCert; int /*<<< orphan*/  lock; int /*<<< orphan*/ * ServerCert; int /*<<< orphan*/ * Policy; int /*<<< orphan*/  Auth; int /*<<< orphan*/  Option; scalar_t__ Offline; } ;
typedef  TYPE_1__ LINK ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  CfgAddBool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  CfgAddBuf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CfgCreateFolder (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  CiWriteClientAuth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CiWriteClientOption (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SiWritePolicyCfg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * XToBuf (int /*<<< orphan*/ *,int) ; 

void SiWriteHubLinkCfg(FOLDER *f, LINK *k)
{
	// Validate arguments
	if (f == NULL || k == NULL)
	{
		return;
	}

	Lock(k->lock);
	{
		// Online
		CfgAddBool(f, "Online", k->Offline ? false : true);

		// Client options
		CiWriteClientOption(CfgCreateFolder(f, "ClientOption"), k->Option);

		// Client authentication data
		CiWriteClientAuth(CfgCreateFolder(f, "ClientAuth"), k->Auth);

		// Policy
		if (k->Policy != NULL)
		{
			SiWritePolicyCfg(CfgCreateFolder(f, "Policy"), k->Policy, true);
		}

		CfgAddBool(f, "CheckServerCert", k->CheckServerCert);

		if (k->ServerCert != NULL)
		{
			BUF *b = XToBuf(k->ServerCert, false);
			CfgAddBuf(f, "ServerCert", b);
			FreeBuf(b);
		}
	}
	Unlock(k->lock);
}