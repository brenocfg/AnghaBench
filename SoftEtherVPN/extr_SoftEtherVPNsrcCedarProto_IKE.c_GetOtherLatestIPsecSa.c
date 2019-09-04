#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_10__ {int /*<<< orphan*/  IPsecSaList; } ;
struct TYPE_9__ {scalar_t__ ServerToClient; int Deleting; scalar_t__ LastCommTick; TYPE_1__* PairIPsecSa; scalar_t__ Established; int /*<<< orphan*/ * IkeClient; } ;
struct TYPE_8__ {scalar_t__ LastCommTick; } ;
typedef  TYPE_2__ IPSECSA ;
typedef  TYPE_3__ IKE_SERVER ;

/* Variables and functions */
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 

IPSECSA *GetOtherLatestIPsecSa(IKE_SERVER *ike, IPSECSA *sa)
{
	UINT i;
	UINT64 min_value = 0;
	IPSECSA *max_sa = NULL;
	// Validate arguments
	if (ike == NULL || sa == NULL)
	{
		return NULL;
	}

	if (sa->IkeClient == NULL)
	{
		return NULL;
	}

	for (i = 0;i < LIST_NUM(ike->IPsecSaList);i++)
	{
		IPSECSA *sa2 = LIST_DATA(ike->IPsecSaList, i);

		if (sa2 != sa)
		{
			if (sa2->IkeClient == sa->IkeClient)
			{
				if (sa2->ServerToClient == sa->ServerToClient)
				{
					if (sa2->Deleting == false)
					{
						if (sa2->Established)
						{
							UINT64 last_comm_tick = sa2->LastCommTick;

							if (sa2->ServerToClient)
							{
								if (sa2->PairIPsecSa != NULL)
								{
									last_comm_tick = sa2->PairIPsecSa->LastCommTick;
								}
							}

							if (min_value < last_comm_tick)
							{
								min_value = last_comm_tick;

								max_sa = sa2;
							}
						}
					}
				}
			}
		}
	}

	return max_sa;
}