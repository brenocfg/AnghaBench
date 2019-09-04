#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X ;
struct TYPE_9__ {TYPE_1__* HubDb; } ;
struct TYPE_8__ {TYPE_4__* Hub; } ;
struct TYPE_7__ {int LinkModeClient; TYPE_3__* Link; } ;
struct TYPE_6__ {int /*<<< orphan*/  RootCertList; } ;
typedef  TYPE_2__ SESSION ;
typedef  TYPE_3__ LINK ;
typedef  TYPE_4__ HUB ;

/* Variables and functions */
 int /*<<< orphan*/ * GetIssuerFromList (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

bool CheckSignatureByCaLinkMode(SESSION *s, X *x)
{
	LINK *k;
	HUB *h;
	bool ret = false;
	// Validate arguments
	if (s == NULL || x == NULL)
	{
		return false;
	}

	if (s->LinkModeClient == false || (k = s->Link) == NULL)
	{
		return false;
	}

	h = k->Hub;

	if (h->HubDb != NULL)
	{
		LockList(h->HubDb->RootCertList);
		{
			X *root_cert;
			root_cert = GetIssuerFromList(h->HubDb->RootCertList, x);
			if (root_cert != NULL)
			{
				ret = true;
			}
		}
		UnlockList(h->HubDb->RootCertList);
	}

	return ret;
}