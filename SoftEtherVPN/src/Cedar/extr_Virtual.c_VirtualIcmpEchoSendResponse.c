#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VH ;
typedef  int /*<<< orphan*/  USHORT ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_5__ {void* SeqNo; void* Identifier; } ;
typedef  TYPE_1__ ICMP_ECHO ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,void*,scalar_t__) ; 
 void* Endian16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  VirtualIcmpSend (int /*<<< orphan*/ *,scalar_t__,scalar_t__,TYPE_1__*,scalar_t__) ; 
 TYPE_1__* ZeroMalloc (scalar_t__) ; 

void VirtualIcmpEchoSendResponse(VH *v, UINT src_ip, UINT dst_ip, USHORT id, USHORT seq_no, void *data, UINT size)
{
	ICMP_ECHO *e;
	// Validate arguments
	if (v == NULL || data == NULL)
	{
		return;
	}

	// Build the header
	e = ZeroMalloc(sizeof(ICMP_ECHO) + size);
	e->Identifier = Endian16(id);
	e->SeqNo = Endian16(seq_no);

	// Data copy
	Copy(((UCHAR *)e) + sizeof(ICMP_ECHO), data, size);

	// Send an ICMP
	VirtualIcmpSend(v, src_ip, dst_ip, e, sizeof(ICMP_ECHO) + size);

	// Release the memory
	Free(e);
}