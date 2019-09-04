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
typedef  scalar_t__ USHORT ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_2__ {int /*<<< orphan*/  Protocol; } ;
typedef  TYPE_1__ MAC_HEADER ;

/* Variables and functions */
 int AdjustTcpMssL3 (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ Endian16 (int /*<<< orphan*/ ) ; 
 scalar_t__ MAC_PROTO_IPV4 ; 
 scalar_t__ MAC_PROTO_IPV6 ; 
 scalar_t__ MAC_PROTO_TAGVLAN ; 
 scalar_t__ READ_USHORT (int /*<<< orphan*/ *) ; 

bool AdjustTcpMssL2(UCHAR *src, UINT src_size, UINT mss, USHORT tag_vlan_tpid)
{
	MAC_HEADER *mac;
	USHORT proto;
	// Validate arguments
	if (src == NULL || src_size == 0 || mss == 0)
	{
		return false;
	}
	if (tag_vlan_tpid == 0)
	{
		tag_vlan_tpid = MAC_PROTO_TAGVLAN;
	}

	if (src_size < sizeof(MAC_HEADER))
	{
		return false;
	}

	mac = (MAC_HEADER *)src;

	src += sizeof(MAC_HEADER);
	src_size -= sizeof(MAC_HEADER);

	proto = Endian16(mac->Protocol);

	if (proto == MAC_PROTO_IPV4 || proto == MAC_PROTO_IPV6)
	{
		// Ordinary IPv4 / IPv6 packet
		return AdjustTcpMssL3(src, src_size, mss);
	}
	else if (proto == tag_vlan_tpid)
	{
		// IPv4 / IPv6 packets in the VLAN tag
		if (src_size < 4)
		{
			return false;
		}

		src += 2;
		src_size -= 2;

		proto = READ_USHORT(src);

		if (proto == MAC_PROTO_IPV4 || proto == MAC_PROTO_IPV6)
		{
			if (mss >= 5)
			{
				mss -= 4;

				src += 2;
				src_size -= 2;

				return AdjustTcpMssL3(src, src_size, mss);
			}
		}
	}

	return false;
}