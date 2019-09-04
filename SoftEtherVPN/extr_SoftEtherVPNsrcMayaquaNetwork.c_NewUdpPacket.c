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
typedef  scalar_t__ UINT ;
struct TYPE_4__ {scalar_t__ DestPort; int /*<<< orphan*/  DstIP; scalar_t__ SrcPort; int /*<<< orphan*/  SrcIP; scalar_t__ Size; void* Data; } ;
typedef  TYPE_1__ UDPPACKET ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* ZeroMalloc (int) ; 

UDPPACKET *NewUdpPacket(IP *src_ip, UINT src_port, IP *dst_ip, UINT dst_port, void *data, UINT size)
{
	UDPPACKET *p;
	// Validate arguments
	if (data == NULL || size == 0 || dst_ip == NULL || dst_port == 0)
	{
		return NULL;
	}

	p = ZeroMalloc(sizeof(UDPPACKET));

	p->Data = data;
	p->Size = size;

	Copy(&p->SrcIP, src_ip, sizeof(IP));
	p->SrcPort = src_port;

	Copy(&p->DstIP, dst_ip, sizeof(IP));
	p->DestPort = dst_port;

	return p;
}