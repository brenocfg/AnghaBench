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
typedef  scalar_t__ USHORT ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_6__ {int /*<<< orphan*/  NextId; TYPE_1__* v; } ;
struct TYPE_5__ {scalar_t__ IpMss; } ;
typedef  TYPE_2__ NATIVE_NAT ;

/* Variables and functions */
 scalar_t__ IP_HEADER_SIZE ; 
 scalar_t__ MAX (scalar_t__,int) ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  NnIpSendFragmentedForInternet (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

void NnIpSendForInternet(NATIVE_NAT *t, UCHAR ip_protocol, UCHAR ttl, UINT src_ip, UINT dest_ip, void *data, UINT size, UINT max_l3_size)
{
	UINT mss = 0;
	UCHAR *buf;
	USHORT offset;
	USHORT id;
	USHORT total_size;
	UINT size_of_this_packet;
	// Validate arguments
	if (t == NULL || data == NULL)
	{
		return;
	}

	// Maximum segment size
	if (max_l3_size > IP_HEADER_SIZE)
	{
		mss = max_l3_size - IP_HEADER_SIZE;
	}

	if (mss == 0)
	{
		mss = t->v->IpMss;
	}

	mss = MAX(mss, 1000);

	// Buffer
	buf = (UCHAR *)data;

	// ID
	id = (t->NextId++);

	// Total size
	total_size = (USHORT)size;

	// Start to fragment
	offset = 0;

	while (true)
	{
		bool last_packet = false;
		// Get the size of this packet
		size_of_this_packet = MIN((USHORT)mss, (total_size - offset));
		if ((offset + (USHORT)size_of_this_packet) == total_size)
		{
			last_packet = true;
		}

		// Transmit the fragmented packet
		NnIpSendFragmentedForInternet(t, ip_protocol, src_ip, dest_ip, id, total_size, offset,
			buf + offset, size_of_this_packet, ttl);
		if (last_packet)
		{
			break;
		}

		offset += (USHORT)size_of_this_packet;
	}
}