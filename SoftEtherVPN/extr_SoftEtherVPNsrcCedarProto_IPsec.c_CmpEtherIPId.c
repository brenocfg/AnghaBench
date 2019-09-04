#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  Id; } ;
typedef  TYPE_1__ ETHERIP_ID ;

/* Variables and functions */
 int StrCmpi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int CmpEtherIPId(void *p1, void *p2)
{
	ETHERIP_ID *k1, *k2;
	// Validate arguments
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}
	k1 = *(ETHERIP_ID **)p1;
	k2 = *(ETHERIP_ID **)p2;
	if (k1 == NULL || k2 == NULL)
	{
		return 0;
	}

	return StrCmpi(k1->Id, k2->Id);
}