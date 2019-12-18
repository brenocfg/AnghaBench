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
typedef  scalar_t__ UINT ;
struct TYPE_2__ {scalar_t__ HashCodeForSend; scalar_t__ Protocol; scalar_t__ SrcIp; scalar_t__ SrcPort; scalar_t__ DestIp; scalar_t__ DestPort; } ;
typedef  TYPE_1__ NATIVE_NAT_ENTRY ;

/* Variables and functions */
 scalar_t__ INFINITE ; 
 scalar_t__ NAT_TCP ; 

UINT GetHashNativeNatTableForSend(void *p)
{
	UINT r;
	NATIVE_NAT_ENTRY *e = (NATIVE_NAT_ENTRY *)p;
	if (e == NULL)
	{
		return 0;
	}

	if (e->HashCodeForSend != INFINITE)
	{
		return e->HashCodeForSend;
	}

	r = 0;

	r += e->Protocol;
	r += e->SrcIp;
	r += e->SrcPort;

	if (e->Protocol == NAT_TCP)
	{
		r += e->DestIp;
		r += e->DestPort;
	}

	e->HashCodeForSend = r;

	return r;
}