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
struct TYPE_10__ {int /*<<< orphan*/  Cedar; } ;
struct TYPE_9__ {int Offline; int /*<<< orphan*/  ServerCert; void* CheckServerCert; } ;
typedef  int /*<<< orphan*/  POLICY ;
typedef  TYPE_1__ LINK ;
typedef  TYPE_2__ HUB ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  int /*<<< orphan*/  CLIENT_OPTION ;
typedef  int /*<<< orphan*/  CLIENT_AUTH ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  BufToX (int /*<<< orphan*/ *,int) ; 
 void* CfgGetBool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * CfgGetBuf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * CfgGetFolder (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  CiFreeClientAuth (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CiLoadClientAuth (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CiLoadClientOption (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 TYPE_1__* NewLink (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseLink (TYPE_1__*) ; 
 int /*<<< orphan*/  SetLinkOffline (TYPE_1__*) ; 
 int /*<<< orphan*/  SetLinkOnline (TYPE_1__*) ; 
 int /*<<< orphan*/  SiLoadPolicyCfg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void SiLoadHubLinkCfg(FOLDER *f, HUB *h)
{
	bool online;
	CLIENT_OPTION *o;
	CLIENT_AUTH *a;
	FOLDER *pf;
	POLICY p;
	LINK *k;
	// Validate arguments
	if (f == NULL || h == NULL)
	{
		return;
	}

	pf = CfgGetFolder(f, "Policy");
	if (pf == NULL)
	{
		return;
	}

	SiLoadPolicyCfg(&p, pf);

	online = CfgGetBool(f, "Online");

	o = CiLoadClientOption(CfgGetFolder(f, "ClientOption"));
	a = CiLoadClientAuth(CfgGetFolder(f, "ClientAuth"));
	if (o == NULL || a == NULL)
	{
		Free(o);
		CiFreeClientAuth(a);
		return;
	}

	k = NewLink(h->Cedar, h, o, a, &p);
	if (k != NULL)
	{
		BUF *b;
		k->CheckServerCert = CfgGetBool(f, "CheckServerCert");
		b = CfgGetBuf(f, "ServerCert");
		if (b != NULL)
		{
			k->ServerCert = BufToX(b, false);
			FreeBuf(b);
		}

		if (online)
		{
			k->Offline = true;
			SetLinkOnline(k);
		}
		else
		{
			k->Offline = false;
			SetLinkOffline(k);
		}
		ReleaseLink(k);
	}

	Free(o);
	CiFreeClientAuth(a);
}