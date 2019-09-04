#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  CryptoKey; int /*<<< orphan*/  SAi_b; int /*<<< orphan*/  GXr; int /*<<< orphan*/  GXi; int /*<<< orphan*/  YourIDPayloadForAM; int /*<<< orphan*/  DhSharedKey; int /*<<< orphan*/  ResponderRand; int /*<<< orphan*/  InitiatorRand; int /*<<< orphan*/  SendBuffer; } ;
typedef  TYPE_1__ IKE_SA ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IkeFreeKey (int /*<<< orphan*/ ) ; 

void FreeIkeSa(IKE_SA *sa)
{
	// Validate arguments
	if (sa == NULL)
	{
		return;
	}

	FreeBuf(sa->SendBuffer);

	FreeBuf(sa->InitiatorRand);
	FreeBuf(sa->ResponderRand);
	FreeBuf(sa->DhSharedKey);
	FreeBuf(sa->YourIDPayloadForAM);

	FreeBuf(sa->GXi);
	FreeBuf(sa->GXr);

	FreeBuf(sa->SAi_b);

	IkeFreeKey(sa->CryptoKey);

	Free(sa);
}