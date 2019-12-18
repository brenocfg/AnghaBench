#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_7__ {int /*<<< orphan*/  SendControlPacketList; int /*<<< orphan*/  NextSendPacketId; } ;
struct TYPE_6__ {int NoResend; scalar_t__ NextSendTime; scalar_t__ DataSize; int /*<<< orphan*/  Data; scalar_t__ PacketId; int /*<<< orphan*/  OpCode; } ;
typedef  TYPE_1__ OPENVPN_CONTROL_PACKET ;
typedef  TYPE_2__ OPENVPN_CHANNEL ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Clone (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_1__* ZeroMalloc (int) ; 

void OvsSendControlPacketEx(OPENVPN_CHANNEL *c, UCHAR opcode, UCHAR *data, UINT data_size, bool no_resend)
{
	OPENVPN_CONTROL_PACKET *p;
	// Validate arguments
	if (c == NULL || (data_size != 0 && data == NULL))
	{
		return;
	}

	p = ZeroMalloc(sizeof(OPENVPN_CONTROL_PACKET));

	p->NoResend = no_resend;

	p->OpCode = opcode;
	p->PacketId = c->NextSendPacketId++;

	if (data != NULL)
	{
		p->Data = Clone(data, data_size);
		p->DataSize = data_size;
	}

	p->NextSendTime = 0;

	Add(c->SendControlPacketList, p);
}