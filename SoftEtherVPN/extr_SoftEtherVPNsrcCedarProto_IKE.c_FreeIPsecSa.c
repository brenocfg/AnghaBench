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
struct TYPE_4__ {int /*<<< orphan*/  Dh; int /*<<< orphan*/  SharedKey; int /*<<< orphan*/  ResponderRand; int /*<<< orphan*/  InitiatorRand; int /*<<< orphan*/  SendBuffer; int /*<<< orphan*/  CryptoKey; } ;
typedef  TYPE_1__ IPSECSA ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IkeDhFreeCtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IkeFreeKey (int /*<<< orphan*/ ) ; 

void FreeIPsecSa(IPSECSA *sa)
{
	// Validate arguments
	if (sa == NULL)
	{
		return;
	}

	IkeFreeKey(sa->CryptoKey);

	FreeBuf(sa->SendBuffer);

	FreeBuf(sa->InitiatorRand);
	FreeBuf(sa->ResponderRand);

	FreeBuf(sa->SharedKey);

	IkeDhFreeCtx(sa->Dh);

	Free(sa);
}