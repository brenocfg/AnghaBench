#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  InternetSetting; int /*<<< orphan*/  CurrentHostName; } ;
struct TYPE_12__ {int IsEnabled; int /*<<< orphan*/  Event; int /*<<< orphan*/  Lock; TYPE_1__* CurrentSock; TYPE_6__ DDnsStatus; } ;
struct TYPE_11__ {int /*<<< orphan*/  InternetSetting; int /*<<< orphan*/  CurrentHostName; } ;
struct TYPE_10__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ SOCK ;
typedef  int /*<<< orphan*/  INTERNET_SETTING ;
typedef  TYPE_2__ DDNS_CLIENT_STATUS ;
typedef  TYPE_3__ AZURE_CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 scalar_t__ Cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Copy (TYPE_6__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  Disconnect (TYPE_1__*) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSock (TYPE_1__*) ; 
 int /*<<< orphan*/  Set (int /*<<< orphan*/ ) ; 
 scalar_t__ StrCmpi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

void AcApplyCurrentConfig(AZURE_CLIENT *ac, DDNS_CLIENT_STATUS *ddns_status)
{
	bool disconnect_now = false;
	SOCK *disconnect_sock = NULL;
	// Validate arguments
	if (ac == NULL)
	{
		return;
	}

	// Get current DDNS configuration
	Lock(ac->Lock);
	{
		if (ddns_status != NULL)
		{
			if (StrCmpi(ac->DDnsStatus.CurrentHostName, ddns_status->CurrentHostName) != 0)
			{
				// If host name is changed, disconnect current data connection
				disconnect_now = true;
			}

			if (Cmp(&ac->DDnsStatus.InternetSetting, &ddns_status->InternetSetting, sizeof(INTERNET_SETTING)) != 0)
			{
				// If proxy setting is changed, disconnect current data connection
				disconnect_now = true;
			}

			Copy(&ac->DDnsStatus, ddns_status, sizeof(DDNS_CLIENT_STATUS));
		}

		if (ac->IsEnabled == false)
		{
			// If VPN Azure client is disabled, disconnect current data connection
			disconnect_now = true;
		}

		if (disconnect_now)
		{
			if (ac->CurrentSock != NULL)
			{
				disconnect_sock = ac->CurrentSock;
				AddRef(disconnect_sock->ref);
			}
		}
	}
	Unlock(ac->Lock);

	if (disconnect_sock != NULL)
	{
		Disconnect(disconnect_sock);
		ReleaseSock(disconnect_sock);
	}

	Set(ac->Event);
}