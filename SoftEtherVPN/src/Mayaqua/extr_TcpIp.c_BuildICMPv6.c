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
typedef  scalar_t__ UINT ;
typedef  void* UCHAR ;
struct TYPE_6__ {int /*<<< orphan*/  Checksum; void* Code; void* Type; } ;
typedef  int /*<<< orphan*/  IPV6_ADDR ;
typedef  TYPE_1__ ICMP_HEADER ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/ * BuildIPv6 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,void*,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  CalcChecksumForIPv6 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Copy (void*,void*,scalar_t__) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  IP_PROTO_ICMPV6 ; 
 TYPE_1__* ZeroMalloc (scalar_t__) ; 

BUF *BuildICMPv6(IPV6_ADDR *src_ip, IPV6_ADDR *dest_ip, UCHAR hop_limit, UCHAR type, UCHAR code, void *data, UINT size, UINT id)
{
	ICMP_HEADER *icmp;
	void *data_buf;
	BUF *ret;
	// Validate arguments
	if (src_ip == NULL || dest_ip == NULL || data == NULL)
	{
		return NULL;
	}

	// Assemble the header
	icmp = ZeroMalloc(sizeof(ICMP_HEADER) + size);
	data_buf = ((UCHAR *)icmp) + sizeof(ICMP_HEADER);
	Copy(data_buf, data, size);

	icmp->Type = type;
	icmp->Code = code;
	icmp->Checksum = CalcChecksumForIPv6(src_ip, dest_ip, IP_PROTO_ICMPV6, icmp,
		sizeof(ICMP_HEADER) + size, 0);

	ret = BuildIPv6(dest_ip, src_ip, id, IP_PROTO_ICMPV6, hop_limit, icmp,
		sizeof(ICMP_HEADER) + size);

	Free(icmp);

	return ret;
}