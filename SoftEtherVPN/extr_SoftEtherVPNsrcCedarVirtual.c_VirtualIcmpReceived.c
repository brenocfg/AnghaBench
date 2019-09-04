#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VH ;
typedef  scalar_t__ USHORT ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_3__ {scalar_t__ Checksum; int Type; } ;
typedef  TYPE_1__ ICMP_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (char*) ; 
#define  ICMP_TYPE_ECHO_REQUEST 129 
#define  ICMP_TYPE_ECHO_RESPONSE 128 
 scalar_t__ IpChecksum (void*,int) ; 
 int /*<<< orphan*/  VirtualIcmpEchoRequestReceived (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ *,int,int) ; 

void VirtualIcmpReceived(VH *v, UINT src_ip, UINT dst_ip, void *data, UINT size, UCHAR ttl, UCHAR *ip_header, UINT ip_header_size, UINT max_l3_size)
{
	ICMP_HEADER *icmp;
	UINT msg_size;
	USHORT checksum_calc, checksum_original;
	// Validate arguments
	if (v == NULL || data == NULL)
	{
		return;
	}

	// Size check
	if (size < sizeof(ICMP_HEADER))
	{
		return;
	}

	// ICMP header
	icmp = (ICMP_HEADER *)data;

	// Get the ICMP message size
	msg_size = size - sizeof(ICMP_HEADER);

	// Check the checksum of the ICMP header
	checksum_original = icmp->Checksum;
	icmp->Checksum = 0;
	checksum_calc = IpChecksum(data, size);
	icmp->Checksum = checksum_original;

	if (checksum_calc != checksum_original)
	{
		// Checksum is invalid
		Debug("ICMP CheckSum Failed.\n");
		return;
	}

	// Identified by the opcode
	switch (icmp->Type)
	{
	case ICMP_TYPE_ECHO_REQUEST:	// ICMP Echo request
		VirtualIcmpEchoRequestReceived(v, src_ip, dst_ip, ((UCHAR *)data) + sizeof(ICMP_HEADER), msg_size, ttl,
			icmp, size, ip_header, ip_header_size, max_l3_size);
		break;

	case ICMP_TYPE_ECHO_RESPONSE:	// ICMP Echo response
		// Do Nothing
		break;
	}
}