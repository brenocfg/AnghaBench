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
typedef  int UINT ;
typedef  int UCHAR ;
struct TYPE_3__ {int TotalHeaderSize; int /*<<< orphan*/ * IPv6Header; } ;
typedef  int /*<<< orphan*/  TCP_HEADER ;
typedef  TYPE_1__ IPV6_HEADER_PACKET_INFO ;
typedef  int /*<<< orphan*/  IPV6_HEADER ;
typedef  int /*<<< orphan*/  IPV4_HEADER ;

/* Variables and functions */
 int IPV4_GET_HEADER_LEN (int /*<<< orphan*/ *) ; 
 int ParsePacketIPv6Header (TYPE_1__*,int*,int) ; 

UINT GetIpHeaderSize(UCHAR *src, UINT src_size)
{
	UCHAR ip_ver;
	TCP_HEADER *tcp = NULL;
	IPV4_HEADER *ip = NULL;
	IPV6_HEADER *ip6 = NULL;
	// Validate arguments
	if (src == NULL || src_size == 0)
	{
		return 0;
	}

	// Get the IP version number
	ip_ver = (src[0] >> 4) & 0x0f;

	if (ip_ver == 4)
	{
		// IPv4
		UINT ip_header_size;
		if (src_size < sizeof(IPV4_HEADER))
		{
			// No IPv4 header
			return 0;
		}

		ip = (IPV4_HEADER *)src;

		ip_header_size = IPV4_GET_HEADER_LEN(ip) * 4;
		if (ip_header_size < sizeof(IPV4_HEADER))
		{
			// Header size is invalid
			return 0;
		}

		if (src_size < ip_header_size)
		{
			// No IPv4 header
			return 0;
		}

		return ip_header_size;
	}
	else if (ip_ver == 6)
	{
		// IPv6
		IPV6_HEADER_PACKET_INFO v6;

		if (ParsePacketIPv6Header(&v6, src, src_size) == false)
		{
			// IPv6 analysis failure
			return 0;
		}

		ip6 = v6.IPv6Header;
		if (ip6 == NULL)
		{
			return 0;
		}

		if (src_size < v6.TotalHeaderSize)
		{
			// No header data
			return 0;
		}

		return v6.TotalHeaderSize;
	}
	else
	{
		// Invalid
		return 0;
	}
}