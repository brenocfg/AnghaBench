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
typedef  scalar_t__ UINT ;
struct TYPE_8__ {int /*<<< orphan*/  IPsecSaList; } ;
struct TYPE_7__ {int ServerToClient; scalar_t__ Spi; } ;
typedef  TYPE_1__ IPSECSA ;
typedef  TYPE_2__ IKE_SERVER ;

/* Variables and functions */
 TYPE_1__* Search (int /*<<< orphan*/ ,TYPE_1__*) ; 

IPSECSA *SearchClientToServerIPsecSaBySpi(IKE_SERVER *ike, UINT spi)
{
	IPSECSA t;
	// Validate arguments
	if (ike == NULL || spi == 0)
	{
		return NULL;
	}

	t.ServerToClient = false;
	t.Spi = spi;

	return Search(ike->IPsecSaList, &t);
}