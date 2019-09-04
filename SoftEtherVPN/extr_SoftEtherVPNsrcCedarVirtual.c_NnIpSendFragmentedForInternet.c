#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int USHORT ;
typedef  int UINT ;
typedef  scalar_t__ UCHAR ;
struct TYPE_14__ {scalar_t__ num_item; } ;
struct TYPE_13__ {int SrcIP; int DstIP; scalar_t__ Checksum; scalar_t__ Protocol; scalar_t__ TimeToLive; scalar_t__* FlagsAndFragmentOffset; void* Identification; void* TotalLength; int /*<<< orphan*/  TypeOfService; scalar_t__ VersionAndHeaderLength; } ;
struct TYPE_12__ {int SendStateChanged; TYPE_3__* SendQueue; } ;
typedef  TYPE_1__ NATIVE_NAT ;
typedef  TYPE_2__ IPV4_HEADER ;
typedef  int /*<<< orphan*/  BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (scalar_t__*,void*,int) ; 
 int /*<<< orphan*/  DEFAULT_IP_TOS ; 
 scalar_t__ DEFAULT_IP_TTL ; 
 void* Endian16 (int) ; 
 int /*<<< orphan*/  FreeBlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPV4_SET_FLAGS (TYPE_2__*,int) ; 
 int /*<<< orphan*/  IPV4_SET_HEADER_LEN (TYPE_2__*,int) ; 
 int /*<<< orphan*/  IPV4_SET_OFFSET (TYPE_2__*,int) ; 
 int /*<<< orphan*/  IPV4_SET_VERSION (TYPE_2__*,int) ; 
 int IP_HEADER_SIZE ; 
 int /*<<< orphan*/  InsertQueue (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ IpChecksum (TYPE_2__*,int) ; 
 int /*<<< orphan*/  LockQueue (TYPE_3__*) ; 
 scalar_t__* Malloc (int) ; 
 scalar_t__ NN_MAX_QUEUE_LENGTH ; 
 int /*<<< orphan*/ * NewBlock (scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockQueue (TYPE_3__*) ; 

void NnIpSendFragmentedForInternet(NATIVE_NAT *t, UCHAR ip_protocol, UINT src_ip, UINT dest_ip, USHORT id, USHORT total_size,
								   USHORT offset, void *data, UINT size, UCHAR ttl)
{
	UCHAR *buf;
	IPV4_HEADER *ip;
	BLOCK *b;
	// Validate arguments
	if (t == NULL || data == NULL)
	{
		return;
	}

	// Memory allocation
	buf = Malloc(size + IP_HEADER_SIZE);
	ip = (IPV4_HEADER *)&buf[0];

	// IP header construction
	ip->VersionAndHeaderLength = 0;
	IPV4_SET_VERSION(ip, 4);
	IPV4_SET_HEADER_LEN(ip, (IP_HEADER_SIZE / 4));
	ip->TypeOfService = DEFAULT_IP_TOS;
	ip->TotalLength = Endian16((USHORT)(size + IP_HEADER_SIZE));
	ip->Identification = Endian16(id);
	ip->FlagsAndFragmentOffset[0] = ip->FlagsAndFragmentOffset[1] = 0;
	IPV4_SET_OFFSET(ip, (offset / 8));
	if ((offset + size) >= total_size)
	{
		IPV4_SET_FLAGS(ip, 0x00);
	}
	else
	{
		IPV4_SET_FLAGS(ip, 0x01);
	}
	ip->TimeToLive = (ttl == 0 ? DEFAULT_IP_TTL : ttl);
	ip->Protocol = ip_protocol;
	ip->Checksum = 0;
	ip->SrcIP = src_ip;
	ip->DstIP = dest_ip;

	// Checksum calculation
	ip->Checksum = IpChecksum(ip, IP_HEADER_SIZE);

	// Data copy
	Copy(buf + IP_HEADER_SIZE, data, size);

	// Transmission
	b = NewBlock(buf, size + IP_HEADER_SIZE, 0);

	LockQueue(t->SendQueue);
	{
		if (t->SendQueue->num_item <= NN_MAX_QUEUE_LENGTH)
		{
			InsertQueue(t->SendQueue, b);

			t->SendStateChanged = true;
		}
		else
		{
			FreeBlock(b);
		}
	}
	UnlockQueue(t->SendQueue);
}