#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VH_OPTION ;
struct TYPE_6__ {int Online; int /*<<< orphan*/  Cedar; int /*<<< orphan*/ * Virtual; int /*<<< orphan*/  Option; int /*<<< orphan*/ * ClientAuth; int /*<<< orphan*/ * ClientOption; int /*<<< orphan*/ * SecureNAT; int /*<<< orphan*/  HaltEvent; int /*<<< orphan*/  HashedPassword; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  SNAT ;
typedef  TYPE_1__ NAT ;

/* Variables and functions */
 int /*<<< orphan*/  NewEvent () ; 
 int /*<<< orphan*/  NewLock () ; 
 void* NewVirtualHostEx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  NiInitConfig (TYPE_1__*) ; 
 int /*<<< orphan*/  Sha0 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* ZeroMalloc (int) ; 

NAT *NiNewNatEx(SNAT *snat, VH_OPTION *o)
{
	NAT *n = ZeroMalloc(sizeof(NAT));

	n->lock = NewLock();
	Sha0(n->HashedPassword, "", 0);
	n->HaltEvent = NewEvent();

	//n->Cedar = NewCedar(NULL, NULL);

	n->SecureNAT = snat;

	// Raise the priority
	//OSSetHighPriority();

	// Initialize the settings
	NiInitConfig(n);

#if	0
	// Start the operation of the virtual host
	if (n->Online && n->ClientOption != NULL)
	{
		n->Virtual = NewVirtualHostEx(n->Cedar, n->ClientOption, n->ClientAuth, &n->Option, n);
	}
	else
	{
		n->Online = false;
		n->Virtual = NULL;
	}
#else
	n->Virtual = NewVirtualHostEx(n->Cedar, NULL, NULL, o, n);
	n->Online = true;
#endif

	// Start management command
	//NiInitAdminAccept(n);

	return n;
}