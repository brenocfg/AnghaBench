#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_3__ {int /*<<< orphan*/ ** IkeCryptos; int /*<<< orphan*/ ** EspCryptos; } ;
typedef  TYPE_1__ IKE_ENGINE ;
typedef  int /*<<< orphan*/  IKE_CRYPTO ;

/* Variables and functions */
 size_t MAX_IKE_ENGINE_ELEMENTS ; 

IKE_CRYPTO *GetIkeCrypto(IKE_ENGINE *e, bool for_esp, UINT i)
{
	// Validate arguments
	if (e == NULL || i == 0 || i >= MAX_IKE_ENGINE_ELEMENTS)
	{
		return NULL;
	}

	if (for_esp)
	{
		return e->EspCryptos[i];
	}
	else
	{
		return e->IkeCryptos[i];
	}
}