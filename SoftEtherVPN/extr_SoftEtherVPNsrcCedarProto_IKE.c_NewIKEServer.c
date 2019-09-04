#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  ref; } ;
struct TYPE_7__ {int /*<<< orphan*/  ThreadList; int /*<<< orphan*/  Engine; void* ClientList; void* IPsecSaList; void* IkeSaList; void* SendPacketList; int /*<<< orphan*/  Now; int /*<<< orphan*/ * IPsec; TYPE_2__* Cedar; } ;
typedef  int /*<<< orphan*/  IPSEC_SERVER ;
typedef  TYPE_1__ IKE_SERVER ;
typedef  TYPE_2__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CmpIPsecSa ; 
 int /*<<< orphan*/ * CmpIkeClient ; 
 int /*<<< orphan*/ * CmpIkeSa ; 
 int /*<<< orphan*/  IPsecLog (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  NewIkeEngine () ; 
 void* NewList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NewThreadList () ; 
 int /*<<< orphan*/  Tick64 () ; 
 TYPE_1__* ZeroMalloc (int) ; 

IKE_SERVER *NewIKEServer(CEDAR *cedar, IPSEC_SERVER *ipsec)
{
	IKE_SERVER *ike;
	// Validate arguments
	if (cedar == NULL)
	{
		return NULL;
	}

	ike = ZeroMalloc(sizeof(IKE_SERVER));

	ike->Cedar = cedar;
	AddRef(cedar->ref);

	ike->IPsec = ipsec;

	ike->Now = Tick64();

	ike->SendPacketList = NewList(NULL);

	ike->IkeSaList = NewList(CmpIkeSa);

	ike->IPsecSaList = NewList(CmpIPsecSa);

	ike->ClientList = NewList(CmpIkeClient);

	ike->Engine = NewIkeEngine();

	ike->ThreadList = NewThreadList();

	IPsecLog(ike, NULL, NULL, NULL, "LI_START");

	return ike;
}