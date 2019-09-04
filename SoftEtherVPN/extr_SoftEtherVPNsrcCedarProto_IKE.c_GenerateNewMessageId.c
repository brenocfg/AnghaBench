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
typedef  int UINT ;
struct TYPE_6__ {int /*<<< orphan*/  IPsecSaList; } ;
struct TYPE_5__ {int MessageId; } ;
typedef  TYPE_1__ IPSECSA ;
typedef  TYPE_2__ IKE_SERVER ;

/* Variables and functions */
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ ,int) ; 
 int LIST_NUM (int /*<<< orphan*/ ) ; 
 int Rand32 () ; 

UINT GenerateNewMessageId(IKE_SERVER *ike)
{
	UINT ret;
	// Validate arguments
	if (ike == NULL)
	{
		return 0;
	}

	while (true)
	{
		ret = Rand32();

		if (ret != 0 && ret != 0xffffffff)
		{
			UINT i;
			bool ok = true;

			for (i = 0;i < LIST_NUM(ike->IPsecSaList);i++)
			{
				IPSECSA *sa = LIST_DATA(ike->IPsecSaList, i);

				if (sa->MessageId == ret)
				{
					ok = false;
					break;
				}
			}

			if (ok)
			{
				return ret;
			}
		}
	}
}