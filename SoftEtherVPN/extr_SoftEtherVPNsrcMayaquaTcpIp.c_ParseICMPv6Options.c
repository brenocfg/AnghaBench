#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_6__ {int Length; int Type; } ;
struct TYPE_5__ {int /*<<< orphan*/ * Mtu; int /*<<< orphan*/ * Prefix; int /*<<< orphan*/ * TargetLinkLayer; int /*<<< orphan*/ * SourceLinkLayer; } ;
typedef  int /*<<< orphan*/  ICMPV6_OPTION_PREFIX ;
typedef  int /*<<< orphan*/  ICMPV6_OPTION_MTU ;
typedef  TYPE_1__ ICMPV6_OPTION_LIST ;
typedef  int /*<<< orphan*/  ICMPV6_OPTION_LINK_LAYER ;
typedef  TYPE_2__ ICMPV6_OPTION ;

/* Variables and functions */
#define  ICMPV6_OPTION_TYPE_MTU 131 
#define  ICMPV6_OPTION_TYPE_PREFIX 130 
#define  ICMPV6_OPTION_TYPE_SOURCE_LINK_LAYER 129 
#define  ICMPV6_OPTION_TYPE_TARGET_LINK_LAYER 128 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

bool ParseICMPv6Options(ICMPV6_OPTION_LIST *o, UCHAR *buf, UINT size)
{
	// Validate arguments
	if (o == NULL || buf == NULL)
	{
		return false;
	}

	Zero(o, sizeof(ICMPV6_OPTION_LIST));

	// Read the header part
	while (true)
	{
		ICMPV6_OPTION *option_header;
		UINT header_total_size;
		UCHAR *header_pointer;
		if (size < sizeof(ICMPV6_OPTION))
		{
			// Size shortage
			return true;
		}

		option_header = (ICMPV6_OPTION *)buf;
		// Calculate the entire header size
		header_total_size = option_header->Length * 8;
		if (header_total_size == 0)
		{
			// The size is zero
			return true;
		}
		if (size < header_total_size)
		{
			// Size shortage
			return true;
		}

		header_pointer = buf;
		buf += header_total_size;
		size -= header_total_size;

		switch (option_header->Type)
		{
		case ICMPV6_OPTION_TYPE_SOURCE_LINK_LAYER:
		case ICMPV6_OPTION_TYPE_TARGET_LINK_LAYER:
			// Source or target link-layer option
			if (header_total_size >= sizeof(ICMPV6_OPTION_LINK_LAYER))
			{
				if (option_header->Type == ICMPV6_OPTION_TYPE_SOURCE_LINK_LAYER)
				{
					o->SourceLinkLayer = (ICMPV6_OPTION_LINK_LAYER *)header_pointer;
				}
				else
				{
					o->TargetLinkLayer = (ICMPV6_OPTION_LINK_LAYER *)header_pointer;
				}
			}
			else
			{
				// ICMPv6 packet corruption?
				return false;
			}
			break;

		case ICMPV6_OPTION_TYPE_PREFIX:
			// Prefix Information
			if (header_total_size >= sizeof(ICMPV6_OPTION_PREFIX))
			{
				o->Prefix = (ICMPV6_OPTION_PREFIX *)header_pointer;
			}
			else
			{
				// ICMPv6 packet corruption?
			}
			break;

		case ICMPV6_OPTION_TYPE_MTU:
			// MTU
			if (header_total_size >= sizeof(ICMPV6_OPTION_MTU))
			{
				o->Mtu = (ICMPV6_OPTION_MTU *)header_pointer;
			}
			else
			{
				// ICMPv6 packet corruption?
			}
			break;
		}
	}
}