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
struct TYPE_2__ {scalar_t__ Protocol; scalar_t__ SrcIp; scalar_t__ SrcPort; scalar_t__ DestIp; scalar_t__ DestPort; } ;
typedef  TYPE_1__ NATIVE_NAT_ENTRY ;

/* Variables and functions */
 int COMPARE_RET (scalar_t__,scalar_t__) ; 
 scalar_t__ NAT_TCP ; 

int CmpNativeNatTableForSend(void *p1, void *p2)
{
	int r;
	NATIVE_NAT_ENTRY *e1, *e2;
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}
	e1 = *(NATIVE_NAT_ENTRY **)p1;
	e2 = *(NATIVE_NAT_ENTRY **)p2;
	if (e1 == NULL || e2 == NULL)
	{
		return 0;
	}

	r = COMPARE_RET(e1->Protocol, e2->Protocol);
	if (r != 0)
	{
		return r;
	}

	r = COMPARE_RET(e1->SrcIp, e2->SrcIp);
	if (r != 0)
	{
		return r;
	}

	r = COMPARE_RET(e1->SrcPort, e2->SrcPort);
	if (r != 0)
	{
		return r;
	}

	if (e1->Protocol == NAT_TCP)
	{
		r = COMPARE_RET(e1->DestIp, e2->DestIp);
		if (r != 0)
		{
			return r;
		}

		r = COMPARE_RET(e1->DestPort, e2->DestPort);
		if (r != 0)
		{
			return r;
		}
	}

	return 0;
}