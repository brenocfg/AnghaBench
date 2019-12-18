#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ IcmpApiOk; scalar_t__ IcmpRawSocketOk; TYPE_1__* HubOption; } ;
typedef  TYPE_2__ VH ;
typedef  int /*<<< orphan*/  USHORT ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_11__ {int /*<<< orphan*/  SeqNo; int /*<<< orphan*/  Identifier; } ;
struct TYPE_9__ {scalar_t__ DisableUserModeSecureNAT; } ;
typedef  TYPE_3__ ICMP_ECHO ;

/* Variables and functions */
 int /*<<< orphan*/  Endian16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NnIcmpEchoRecvForInternet (TYPE_2__*,int,int,void*,int,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ NnIsActive (TYPE_2__*) ; 
 int /*<<< orphan*/  VirtualIcmpEchoRequestReceivedRaw (TYPE_2__*,int,int,void*,int,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  VirtualIcmpEchoSendResponse (TYPE_2__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 

void VirtualIcmpEchoRequestReceived(VH *v, UINT src_ip, UINT dst_ip, void *data, UINT size, UCHAR ttl, void *icmp_data, UINT icmp_size, UCHAR *ip_header, UINT ip_header_size, UINT max_l3_size)
{
	ICMP_ECHO *echo;
	UINT data_size;
	void *data_buf;
	USHORT id, seq_no;
	// Validate arguments
	if (v == NULL || data == NULL || icmp_data == NULL)
	{
		return;
	}

	//Debug("ICMP: %u\n", size);

	if (NnIsActive(v))
	{
		// Process by the Native NAT
		NnIcmpEchoRecvForInternet(v, src_ip, dst_ip, data, size, ttl, icmp_data, icmp_size,
			ip_header, ip_header_size, max_l3_size);
		return;
	}

	if (v->HubOption != NULL && v->HubOption->DisableUserModeSecureNAT)
	{
		// User-mode NAT is disabled
		return;
	}

	if (v->IcmpRawSocketOk || v->IcmpApiOk)
	{
		// Process in the Raw Socket
		VirtualIcmpEchoRequestReceivedRaw(v, src_ip, dst_ip, data, size, ttl, icmp_data, icmp_size,
			ip_header, ip_header_size);
		return;
	}

	// Returns the fake ICMP forcibly if any of Native NAT or Raw Socket can not be used

	echo = (ICMP_ECHO *)data;

	// Echo size check
	if (size < sizeof(ICMP_ECHO))
	{
		// Insufficient data
		return;
	}

	id = Endian16(echo->Identifier);
	seq_no = Endian16(echo->SeqNo);

	// Data size
	data_size = size - sizeof(ICMP_ECHO);

	// Data body
	data_buf = ((UCHAR *)data) + sizeof(ICMP_ECHO);

	// Return the ICMP Echo Response
	VirtualIcmpEchoSendResponse(v, dst_ip, src_ip, id, seq_no, data_buf, data_size);
}