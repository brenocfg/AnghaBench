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
typedef  scalar_t__ UINT ;
struct TYPE_4__ {int /*<<< orphan*/  DhsList; int /*<<< orphan*/  HashesList; int /*<<< orphan*/  CryptosList; } ;
typedef  int /*<<< orphan*/  IKE_HASH ;
typedef  TYPE_1__ IKE_ENGINE ;
typedef  int /*<<< orphan*/  IKE_DH ;
typedef  int /*<<< orphan*/  IKE_CRYPTO ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeIkeCrypto (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeIkeDh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeIkeHash (int /*<<< orphan*/ *) ; 
 void* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ ) ; 

void FreeIkeEngine(IKE_ENGINE *e)
{
	UINT i;
	// Validate arguments
	if (e == NULL)
	{
		return;
	}

	for (i = 0;i < LIST_NUM(e->CryptosList);i++)
	{
		IKE_CRYPTO *c = LIST_DATA(e->CryptosList, i);

		FreeIkeCrypto(c);
	}

	ReleaseList(e->CryptosList);

	for (i = 0;i < LIST_NUM(e->HashesList);i++)
	{
		IKE_HASH *h = LIST_DATA(e->HashesList, i);

		FreeIkeHash(h);
	}
	ReleaseList(e->HashesList);

	for (i = 0;i < LIST_NUM(e->DhsList);i++)
	{
		IKE_DH *d = LIST_DATA(e->DhsList, i);

		FreeIkeDh(d);
	}
	ReleaseList(e->DhsList);

	Free(e);
}