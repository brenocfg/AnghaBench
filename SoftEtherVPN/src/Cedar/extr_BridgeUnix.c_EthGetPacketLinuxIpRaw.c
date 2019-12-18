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
struct TYPE_8__ {scalar_t__ Size; void* Buf; } ;
struct TYPE_7__ {int RawIp_HasError; int /*<<< orphan*/  RawIcmp; int /*<<< orphan*/  RawUdp; int /*<<< orphan*/  RawTcp; int /*<<< orphan*/  RawIpSendQueue; } ;
typedef  TYPE_1__ ETH ;
typedef  TYPE_2__ BUF ;

/* Variables and functions */
 scalar_t__ EthGetPacketLinuxIpRawForSock (TYPE_1__*,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_2__*) ; 
 TYPE_2__* GetNext (int /*<<< orphan*/ ) ; 
 scalar_t__ INFINITE ; 
 int /*<<< orphan*/  IP_PROTO_ICMPV4 ; 
 int /*<<< orphan*/  IP_PROTO_TCP ; 
 int /*<<< orphan*/  IP_PROTO_UDP ; 

UINT EthGetPacketLinuxIpRaw(ETH *e, void **data)
{
	UINT r;
	BUF *b;
	// Validate arguments
	if (e == NULL || data == NULL)
	{
		return INFINITE;
	}
	if (e->RawIp_HasError)
	{
		return INFINITE;
	}

	b = GetNext(e->RawIpSendQueue);
	if (b != NULL)
	{
		UINT size;

		*data = b->Buf;
		size = b->Size;

		Free(b);

		return size;
	}

	r = EthGetPacketLinuxIpRawForSock(e, data, e->RawTcp, IP_PROTO_TCP);
	if (r == 0)
	{
		r = EthGetPacketLinuxIpRawForSock(e, data, e->RawUdp, IP_PROTO_UDP);
		if (r == 0)
		{
			r = EthGetPacketLinuxIpRawForSock(e, data, e->RawIcmp, IP_PROTO_ICMPV4);
		}
	}

	if (r == INFINITE)
	{
		e->RawIp_HasError = true;
	}

	return r;
}