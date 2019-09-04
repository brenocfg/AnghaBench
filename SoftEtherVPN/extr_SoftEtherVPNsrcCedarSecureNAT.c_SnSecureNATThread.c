#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_29__ {int /*<<< orphan*/  ref; } ;
struct TYPE_28__ {TYPE_5__* Session; int /*<<< orphan*/  Protocol; } ;
struct TYPE_27__ {int /*<<< orphan*/  ref; } ;
struct TYPE_26__ {int NoBroadcastLimiter; } ;
struct TYPE_25__ {int SecureNATMode; int /*<<< orphan*/  Hub; TYPE_9__* Cancel1; int /*<<< orphan*/  ref; int /*<<< orphan*/  Username; int /*<<< orphan*/  Name; TYPE_4__* SecureNAT; } ;
struct TYPE_24__ {TYPE_3__* Nat; TYPE_5__* Session; TYPE_7__* Hub; int /*<<< orphan*/  Cedar; } ;
struct TYPE_23__ {TYPE_2__* Virtual; } ;
struct TYPE_22__ {TYPE_1__* NativeNat; TYPE_9__* Cancel; } ;
struct TYPE_21__ {int /*<<< orphan*/  CancelLock; TYPE_9__* Cancel; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_4__ SNAT ;
typedef  TYPE_5__ SESSION ;
typedef  TYPE_6__ POLICY ;
typedef  TYPE_7__ HUB ;
typedef  TYPE_8__ CONNECTION ;
typedef  TYPE_9__ CANCEL ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONNECTION_HUB_SECURE_NAT ; 
 TYPE_6__* ClonePolicy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CopyStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Debug (char*) ; 
 int /*<<< orphan*/  GetDefaultPolicy () ; 
 int /*<<< orphan*/  HLog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 TYPE_8__* NewServerConnection (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_5__* NewServerSession (int /*<<< orphan*/ ,TYPE_8__*,TYPE_7__*,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  NoticeThreadInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseCancel (TYPE_9__*) ; 
 int /*<<< orphan*/  ReleaseConnection (TYPE_8__*) ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_7__*) ; 
 int /*<<< orphan*/  ReleaseSession (TYPE_5__*) ; 
 int /*<<< orphan*/  SNAT_USER_NAME ; 
 int /*<<< orphan*/  SNAT_USER_NAME_PRINT ; 
 int /*<<< orphan*/  SessionMain (TYPE_5__*) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

void SnSecureNATThread(THREAD *t, void *param)
{
	SNAT *s;
	CONNECTION *c;
	SESSION *se;
	POLICY *policy;
	HUB *h;
	// Validate arguments
	if (t == NULL || param == NULL)
	{
		return;
	}

	s = (SNAT *)param;
	// Create a server connection
	c = NewServerConnection(s->Cedar, NULL, t);
	c->Protocol = CONNECTION_HUB_SECURE_NAT;

	// Apply the default policy
	policy = ClonePolicy(GetDefaultPolicy());

	// Not to limit the number of broadcast
	policy->NoBroadcastLimiter = true;

	h = s->Hub;
	AddRef(h->ref);

	// create a server session
	se = NewServerSession(s->Cedar, c, s->Hub, SNAT_USER_NAME, policy);
	se->SecureNATMode = true;
	se->SecureNAT = s;
	c->Session = se;
	ReleaseConnection(c);

	HLog(se->Hub, "LH_NAT_START", se->Name);

	// User name
	se->Username = CopyStr(SNAT_USER_NAME_PRINT);

	s->Session = se;
	AddRef(se->ref);

	// Notification initialization completion
	NoticeThreadInit(t);

	ReleaseCancel(s->Nat->Virtual->Cancel);
	s->Nat->Virtual->Cancel = se->Cancel1;
	AddRef(se->Cancel1->ref);

	if (s->Nat->Virtual->NativeNat != NULL)
	{
		CANCEL *old_cancel = NULL;

		Lock(s->Nat->Virtual->NativeNat->CancelLock);
		{
			if (s->Nat->Virtual->NativeNat->Cancel != NULL)
			{
				old_cancel = s->Nat->Virtual->NativeNat->Cancel;

				s->Nat->Virtual->NativeNat->Cancel = se->Cancel1;

				AddRef(se->Cancel1->ref);
			}
		}
		Unlock(s->Nat->Virtual->NativeNat->CancelLock);

		if (old_cancel != NULL)
		{
			ReleaseCancel(old_cancel);
		}
	}

	// Main function of the session
	Debug("SecureNAT Start.\n");
	SessionMain(se);
	Debug("SecureNAT Stop.\n");

	HLog(se->Hub, "LH_NAT_STOP");

	ReleaseHub(h);

	ReleaseSession(se);
}