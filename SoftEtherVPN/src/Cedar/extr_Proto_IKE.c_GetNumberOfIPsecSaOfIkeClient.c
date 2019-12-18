#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_6__ {int /*<<< orphan*/  IPsecSaList; } ;
struct TYPE_5__ {int /*<<< orphan*/ * IkeClient; } ;
typedef  TYPE_1__ IPSECSA ;
typedef  TYPE_2__ IKE_SERVER ;
typedef  int /*<<< orphan*/  IKE_CLIENT ;

/* Variables and functions */
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 

UINT GetNumberOfIPsecSaOfIkeClient(IKE_SERVER *ike, IKE_CLIENT *c)
{
	UINT num = 0, i;
	// Validate arguments
	if (ike == NULL || c == NULL)
	{
		return 0;
	}

	for (i = 0;i < LIST_NUM(ike->IPsecSaList);i++)
	{
		IPSECSA *sa = LIST_DATA(ike->IPsecSaList, i);

		if (sa->IkeClient == c)
		{
			num++;
		}
	}

	return num;
}