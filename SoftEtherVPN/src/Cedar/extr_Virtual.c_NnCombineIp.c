#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_15__ {int Size; int HeadIpHeaderDataSize; int DataReserved; int /*<<< orphan*/  MaxL3Size; int /*<<< orphan*/ * HeadIpHeaderData; int /*<<< orphan*/  Ttl; scalar_t__ Data; int /*<<< orphan*/  Protocol; int /*<<< orphan*/  DestIP; int /*<<< orphan*/  SrcIP; int /*<<< orphan*/  IpParts; } ;
struct TYPE_14__ {int Offset; int Size; } ;
struct TYPE_13__ {int /*<<< orphan*/  IpCombine; int /*<<< orphan*/  CurrentIpQuota; } ;
typedef  TYPE_1__ NATIVE_NAT ;
typedef  TYPE_2__ IP_PART ;
typedef  TYPE_3__ IP_COMBINE ;
typedef  int /*<<< orphan*/  IPV4_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/ * Clone (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ ,int) ; 
 int LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NnFreeIpCombine (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  NnIpReceived (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ReAlloc (scalar_t__,int) ; 
 TYPE_2__* ZeroMalloc (int) ; 

void NnCombineIp(NATIVE_NAT *t, IP_COMBINE *c, UINT offset, void *data, UINT size, bool last_packet, UCHAR *head_ip_header_data, UINT head_ip_header_size)
{
	UINT i;
	IP_PART *p;
	UINT need_size;
	UINT data_size_delta;
	// Validate arguments
	if (c == NULL || data == NULL)
	{
		return;
	}

	// Check the size and offset
	if ((offset + size) > 65535)
	{
		// Do not process a packet larger than 64Kbytes
		return;
	}

	if (last_packet == false && c->Size != 0)
	{
		if ((offset + size) > c->Size)
		{
			// Do not process a packet larger than the packet size
			return;
		}
	}

	if (head_ip_header_data != NULL && head_ip_header_size >= sizeof(IPV4_HEADER))
	{
		if (c->HeadIpHeaderData == NULL)
		{
			c->HeadIpHeaderData = Clone(head_ip_header_data, head_ip_header_size);
			c->HeadIpHeaderDataSize = head_ip_header_size;
		}
	}

	need_size = offset + size;
	data_size_delta = c->DataReserved;
	// Ensure sufficient if the buffer is insufficient
	while (c->DataReserved < need_size)
	{
		c->DataReserved = c->DataReserved * 4;
		c->Data = ReAlloc(c->Data, c->DataReserved);
	}
	data_size_delta = c->DataReserved - data_size_delta;
	t->CurrentIpQuota += data_size_delta;

	// Overwrite the data into the buffer
	Copy(((UCHAR *)c->Data) + offset, data, size);

	if (last_packet)
	{
		// If No More Fragment packet arrives, the size of this datagram is finalized
		c->Size = offset + size;
	}

	// Check the overlap between the region which is represented by the offset and size of the
	// existing received list and the region which is represented by the offset and size
	for (i = 0;i < LIST_NUM(c->IpParts);i++)
	{
		UINT moving_size;
		IP_PART *p = LIST_DATA(c->IpParts, i);

		// Check the overlapping between the existing area and head area
		if ((p->Offset <= offset) && ((p->Offset + p->Size) > offset))
		{
			// Compress behind the offset of this packet since a duplication is
			// found in the first part with the existing packet and this packet

			if ((offset + size) <= (p->Offset + p->Size))
			{
				// This packet is buried in the existing packet
				size = 0;
			}
			else
			{
				// Retral region is not overlapped
				moving_size = p->Offset + p->Size - offset;
				offset += moving_size;
				size -= moving_size;
			}
		}
		if ((p->Offset < (offset + size)) && ((p->Offset + p->Size) >= (offset + size)))
		{
			// Compress the size of this packet forward because a duplication is
			// found between the posterior portion the existing packet and this packet

			moving_size = p->Offset + p->Size - offset - size;
			size -= moving_size;
		}

		if ((p->Offset >= offset) && ((p->Offset + p->Size) <= (offset + size)))
		{
			// This packet was overwritten to completely hunched over a existing packet
			p->Size = 0;
		}
	}

	if (size != 0)
	{
		// Register this packet
		p = ZeroMalloc(sizeof(IP_PART));

		p->Offset = offset;
		p->Size = size;

		Add(c->IpParts, p);
	}

	if (c->Size != 0)
	{
		// Get the total size of the data portion list already received
		UINT total_size = 0;
		UINT i;

		for (i = 0;i < LIST_NUM(c->IpParts);i++)
		{
			IP_PART *p = LIST_DATA(c->IpParts, i);

			total_size += p->Size;
		}

		if (total_size == c->Size)
		{
			// Received whole of the IP packet
			//Debug("Combine: %u\n", total_size);
			NnIpReceived(t, c->SrcIP, c->DestIP, c->Protocol, c->Data, c->Size, c->Ttl,
				c->HeadIpHeaderData, c->HeadIpHeaderDataSize, c->MaxL3Size);

			// Release the combining object
			NnFreeIpCombine(t, c);

			// Remove from the combining object list
			Delete(t->IpCombine, c);
		}
	}
}