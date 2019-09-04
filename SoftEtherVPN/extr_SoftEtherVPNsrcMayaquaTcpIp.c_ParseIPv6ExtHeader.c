#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_5__ {int IsFragment; int HopHeaderSize; int EndPointHeaderSize; int RoutingHeaderSize; int PayloadSize; int /*<<< orphan*/  Protocol; int /*<<< orphan*/ * Payload; int /*<<< orphan*/ * FragmentHeader; TYPE_1__* RoutingHeader; TYPE_1__* EndPointHeader; TYPE_1__* HopHeader; } ;
struct TYPE_4__ {int /*<<< orphan*/  Size; } ;
typedef  TYPE_1__ IPV6_OPTION_HEADER ;
typedef  TYPE_2__ IPV6_HEADER_PACKET_INFO ;
typedef  int /*<<< orphan*/  IPV6_FRAGMENT_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  IPV6_GET_FRAGMENT_OFFSET (int /*<<< orphan*/ *) ; 
#define  IPV6_HEADER_ENDPOINT 131 
#define  IPV6_HEADER_FRAGMENT 130 
#define  IPV6_HEADER_HOP 129 
 int /*<<< orphan*/  IPV6_HEADER_NONE ; 
#define  IPV6_HEADER_ROUTING 128 

bool ParseIPv6ExtHeader(IPV6_HEADER_PACKET_INFO *info, UCHAR next_header, UCHAR *buf, UINT size)
{
	bool ret = false;
	IPV6_OPTION_HEADER *option_header;
	UINT option_header_size;
	UCHAR next_header_2 = IPV6_HEADER_NONE;
	// Validate arguments
	if (info == NULL || buf == NULL)
	{
		return false;
	}

	info->IsFragment = false;

	while (true)
	{
		if (size > 8)
		{
			next_header_2 = *((UCHAR *)buf);
		}

		switch (next_header)
		{
		case IPV6_HEADER_HOP:
		case IPV6_HEADER_ENDPOINT:
		case IPV6_HEADER_ROUTING:
			// Variable-length header
			if (size < 8)
			{
				return false;
			}

			option_header = (IPV6_OPTION_HEADER *)buf;
			option_header_size = (option_header->Size + 1) * 8;
			if (size < option_header_size)
			{
				return false;
			}

			switch (next_header)
			{
			case IPV6_HEADER_HOP:
				info->HopHeader = (IPV6_OPTION_HEADER *)buf;
				info->HopHeaderSize = option_header_size;
				break;

			case IPV6_HEADER_ENDPOINT:
				info->EndPointHeader = (IPV6_OPTION_HEADER *)buf;
				info->EndPointHeaderSize = option_header_size;
				break;

			case IPV6_HEADER_ROUTING:
				info->RoutingHeader = (IPV6_OPTION_HEADER *)buf;
				info->RoutingHeaderSize = option_header_size;
				break;
			}

			buf += option_header_size;
			size -= option_header_size;
			break;

		case IPV6_HEADER_FRAGMENT:
			// Fragment header (fixed length)
			if (size < sizeof(IPV6_FRAGMENT_HEADER))
			{
				return false;
			}

			info->FragmentHeader = (IPV6_FRAGMENT_HEADER *)buf;

			if (IPV6_GET_FRAGMENT_OFFSET(info->FragmentHeader) != 0)
			{
				info->IsFragment = true;
			}

			buf += sizeof(IPV6_FRAGMENT_HEADER);
			size -= sizeof(IPV6_FRAGMENT_HEADER);
			break;

		default:
			// Considered that the payload follows
			if (next_header != IPV6_HEADER_NONE)
			{
				info->Payload = buf;
				info->PayloadSize = size;
			}
			else
			{
				info->Payload = NULL;
				info->PayloadSize = 0;
			}
			info->Protocol = next_header;
			return true;
		}

		next_header = next_header_2;
	}
}