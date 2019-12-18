#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ IpMss; int /*<<< orphan*/  NextId; } ;
typedef  TYPE_1__ VH ;
typedef  scalar_t__ USHORT ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;

/* Variables and functions */
 scalar_t__ MAX_IP_DATA_SIZE_TOTAL ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SendFragmentedIp (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void SendIpEx(VH *v, UINT dest_ip, UINT src_ip, UCHAR protocol, void *data, UINT size, UCHAR ttl)
{
	UINT mss;
	UCHAR *buf;
	USHORT offset;
	USHORT id;
	USHORT total_size;
	UINT size_of_this_packet;
	// Validate arguments
	if (v == NULL || data == NULL || size == 0 || size > MAX_IP_DATA_SIZE_TOTAL)
	{
		return;
	}

	// Maximum segment size
	mss = v->IpMss;

	// Buffer
	buf = (UCHAR *)data;

	// ID
	id = (v->NextId++);

	// Total size
	total_size = (USHORT)size;

	// Start to split
	offset = 0;

	while (true)
	{
		bool last_packet = false;
		// Gets the size of this packet
		size_of_this_packet = MIN((USHORT)mss, (total_size - offset));
		if ((offset + (USHORT)size_of_this_packet) == total_size)
		{
			last_packet = true;
		}

		// Transmit the fragmented packet
		SendFragmentedIp(v, dest_ip, src_ip, id,
			total_size, offset, protocol, buf + offset, size_of_this_packet, NULL, ttl);
		if (last_packet)
		{
			break;
		}

		offset += (USHORT)size_of_this_packet;
	}
}