#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_8__ {TYPE_1__* NatTableForRecv; } ;
struct TYPE_7__ {scalar_t__ SrcIp; scalar_t__ Protocol; } ;
struct TYPE_6__ {int /*<<< orphan*/  AllList; } ;
typedef  TYPE_2__ NATIVE_NAT_ENTRY ;
typedef  TYPE_3__ NATIVE_NAT ;

/* Variables and functions */
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 

UINT NnGetNumNatEntriesPerIp(NATIVE_NAT *t, UINT src_ip, UINT protocol)
{
	UINT ret = 0;
	UINT i;
	// Validate arguments
	if (t == NULL)
	{
		return 0;
	}

	for (i = 0;i < LIST_NUM(t->NatTableForRecv->AllList);i++)
	{
		NATIVE_NAT_ENTRY *e = LIST_DATA(t->NatTableForRecv->AllList, i);

		if (e->SrcIp == src_ip)
		{
			if (e->Protocol == protocol)
			{
				ret++;
			}
		}
	}

	return ret;
}