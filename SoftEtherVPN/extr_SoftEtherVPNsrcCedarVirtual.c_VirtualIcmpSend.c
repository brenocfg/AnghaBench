#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VH ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_6__ {scalar_t__ Checksum; int /*<<< orphan*/  Type; scalar_t__ Code; } ;
typedef  TYPE_1__ ICMP_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (void*,void*,scalar_t__) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  ICMP_TYPE_ECHO_RESPONSE ; 
 int /*<<< orphan*/  IP_PROTO_ICMPV4 ; 
 scalar_t__ IpChecksum (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  SendIp (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,TYPE_1__*,scalar_t__) ; 
 TYPE_1__* ZeroMalloc (scalar_t__) ; 

void VirtualIcmpSend(VH *v, UINT src_ip, UINT dst_ip, void *data, UINT size)
{
	ICMP_HEADER *icmp;
	void *data_buf;
	// Validate arguments
	if (v == NULL || data == NULL)
	{
		return;
	}

	// Build the header
	icmp = ZeroMalloc(sizeof(ICMP_HEADER) + size);
	// Data copy
	data_buf = ((UCHAR *)icmp) + sizeof(ICMP_HEADER);
	Copy(data_buf, data, size);
	// Other
	icmp->Checksum = 0;
	icmp->Code = 0;
	icmp->Type = ICMP_TYPE_ECHO_RESPONSE;
	// Checksum
	icmp->Checksum = IpChecksum(icmp, sizeof(ICMP_HEADER) + size);

	// IP packet transmission
	SendIp(v, dst_ip, src_ip, IP_PROTO_ICMPV4, icmp, sizeof(ICMP_HEADER) + size);

	// Release the memory
	Free(icmp);
}