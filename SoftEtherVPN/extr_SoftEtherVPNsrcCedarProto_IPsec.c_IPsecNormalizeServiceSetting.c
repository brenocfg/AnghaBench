#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  HubList; } ;
struct TYPE_10__ {char* Name; } ;
struct TYPE_8__ {int /*<<< orphan*/  L2TP_DefaultHub; int /*<<< orphan*/  IPsec_Secret; } ;
struct TYPE_9__ {int /*<<< orphan*/  LockSettings; TYPE_1__ Services; TYPE_4__* Cedar; } ;
typedef  TYPE_2__ IPSEC_SERVER ;
typedef  TYPE_3__ HUB ;
typedef  TYPE_4__ CEDAR ;

/* Variables and functions */
 char* IPSEC_DEFAULT_SECRET ; 
 scalar_t__ IsEmptyStr (int /*<<< orphan*/ ) ; 
 int IsHub (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* LIST_DATA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void IPsecNormalizeServiceSetting(IPSEC_SERVER *s)
{
	CEDAR *c;
	// Validate arguments
	if (s == NULL)
	{
		return;
	}

	c = s->Cedar;

	Lock(s->LockSettings);
	{
		bool reset_hub_setting = false;

		if (IsEmptyStr(s->Services.IPsec_Secret))
		{
			// If the secret is not set, set the default one
			StrCpy(s->Services.IPsec_Secret, sizeof(s->Services.IPsec_Secret), IPSEC_DEFAULT_SECRET);
		}

		LockList(c->HubList);
		{
			if (IsEmptyStr(s->Services.L2TP_DefaultHub))
			{
				reset_hub_setting = true;
			}
			else
			{
				if (IsHub(c, s->Services.L2TP_DefaultHub) == false)
				{
					reset_hub_setting = true;
				}
			}

			if (reset_hub_setting)
			{
				// Select the first Virtual HUB if there is no HUB
				HUB *h = NULL;
				
				if (LIST_NUM(c->HubList) >= 1)
				{
					h = LIST_DATA(c->HubList, 0);
				}

				if (h != NULL)
				{
					StrCpy(s->Services.L2TP_DefaultHub, sizeof(s->Services.L2TP_DefaultHub), h->Name);
				}
				else
				{
					StrCpy(s->Services.L2TP_DefaultHub, sizeof(s->Services.L2TP_DefaultHub), "");
				}
			}
		}
		UnlockList(c->HubList);
	}
	Unlock(s->LockSettings);
}