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
struct TYPE_4__ {struct TYPE_4__* Data; int /*<<< orphan*/  AesKey; int /*<<< orphan*/  DesKey3; int /*<<< orphan*/  DesKey2; int /*<<< orphan*/  DesKey1; } ;
typedef  TYPE_1__ IKE_CRYPTO_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  AesFreeKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DesFreeKeyValue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 

void IkeFreeKey(IKE_CRYPTO_KEY *k)
{
	// Validate arguments
	if (k == NULL)
	{
		return;
	}

	DesFreeKeyValue(k->DesKey1);
	DesFreeKeyValue(k->DesKey2);
	DesFreeKeyValue(k->DesKey3);

	AesFreeKey(k->AesKey);

	Free(k->Data);

	Free(k);
}