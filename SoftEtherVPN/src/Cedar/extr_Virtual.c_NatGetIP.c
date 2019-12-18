#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {void* ref; int /*<<< orphan*/  Ip; scalar_t__ Ok; int /*<<< orphan*/  Hostname; } ;
struct TYPE_8__ {int NumTokens; char** Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_2__ NAT_DNS_QUERY ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (void*) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Free (TYPE_2__*) ; 
 int /*<<< orphan*/  FreeToken (TYPE_1__*) ; 
 int GetIP (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  NAT_DNS_QUERY_TIMEOUT ; 
 int /*<<< orphan*/  NatGetIPThread ; 
 void* NewRef () ; 
 int /*<<< orphan*/ * NewThread (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_1__* ParseToken (char*,char*) ; 
 scalar_t__ Release (void*) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* ZeroMalloc (int) ; 

bool NatGetIP(IP *ip, char *hostname)
{
	TOKEN_LIST *t;
	bool ret = false;
	// Validate arguments
	if (ip == NULL || hostname == NULL)
	{
		return false;
	}

	t = ParseToken(hostname, ".");
	if (t == NULL)
	{
		return false;
	}
	if (t->NumTokens == 0)
	{
		FreeToken(t);
		return false;
	}

	if (t->NumTokens == 1)
	{
		ret = GetIP(ip, hostname);
	}
	else
	{
		char *hostname2 = t->Token[0];
		NAT_DNS_QUERY *q1, *q2;
		THREAD *t1, *t2;

		q1 = ZeroMalloc(sizeof(NAT_DNS_QUERY));
		q2 = ZeroMalloc(sizeof(NAT_DNS_QUERY));
		q1->ref = NewRef();
		q2->ref = NewRef();
		AddRef(q1->ref);
		AddRef(q2->ref);
		StrCpy(q1->Hostname, sizeof(q1->Hostname), hostname);
		StrCpy(q2->Hostname, sizeof(q2->Hostname), hostname2);

		t1 = NewThread(NatGetIPThread, q1);
		t2 = NewThread(NatGetIPThread, q2);

		WaitThread(t1, NAT_DNS_QUERY_TIMEOUT);

		if (q1->Ok)
		{
			ret = true;
			Copy(ip, &q1->Ip, sizeof(IP));
		}
		else
		{
			WaitThread(t2, NAT_DNS_QUERY_TIMEOUT);
			if (q1->Ok)
			{
				ret = true;
				Copy(ip, &q1->Ip, sizeof(IP));
			}
			else if (q2->Ok)
			{
				ret = true;
				Copy(ip, &q2->Ip, sizeof(IP));
			}
		}

		ReleaseThread(t1);
		ReleaseThread(t2);

		if (Release(q1->ref) == 0)
		{
			Free(q1);
		}
		if (Release(q2->ref) == 0)
		{
			Free(q2);
		}
	}

	FreeToken(t);

	return ret;
}