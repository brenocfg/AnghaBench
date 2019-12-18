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
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_8__ {int Deleting; scalar_t__ LastCommTick; scalar_t__ Established; int /*<<< orphan*/ * IkeClient; } ;
struct TYPE_7__ {int /*<<< orphan*/  IkeSaList; } ;
typedef  TYPE_1__ IKE_SERVER ;
typedef  TYPE_2__ IKE_SA ;

/* Variables and functions */
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 

IKE_SA *GetOtherLatestIkeSa(IKE_SERVER *ike, IKE_SA *sa)
{
	UINT i;
	UINT64 min_value = 0;
	IKE_SA *max_sa = NULL;
	// Validate arguments
	if (ike == NULL || sa == NULL)
	{
		return NULL;
	}

	if (sa->IkeClient == NULL)
	{
		return NULL;
	}

	for (i = 0;i < LIST_NUM(ike->IkeSaList);i++)
	{
		IKE_SA *sa2 = LIST_DATA(ike->IkeSaList, i);

		if (sa2 != sa)
		{
			if (sa2->IkeClient == sa->IkeClient)
			{
				if (sa2->Deleting == false)
				{
					if (sa2->Established)
					{
						if (min_value < sa2->LastCommTick)
						{
							min_value = sa2->LastCommTick;

							max_sa = sa2;
						}
					}
				}
			}
		}
	}

	return max_sa;
}