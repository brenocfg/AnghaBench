#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
typedef  int UCHAR ;
struct TYPE_3__ {int OpCode; int KeyId; int DataSize; int NumAck; int PacketId; int /*<<< orphan*/ * Data; int /*<<< orphan*/  YourSessionId; scalar_t__* AckPacketId; int /*<<< orphan*/  MySessionId; } ;
typedef  TYPE_1__ OPENVPN_PACKET ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 size_t MIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewBuf () ; 
 int /*<<< orphan*/  OPENVPN_MAX_NUMACK ; 
 int OPENVPN_P_ACK_V1 ; 
 int OPENVPN_P_DATA_V1 ; 
 int /*<<< orphan*/  SeekBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WriteBufChar (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WriteBufInt (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WriteBufInt64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

BUF *OvsBuildPacket(OPENVPN_PACKET *p)
{
	BUF *b;
	UCHAR uc;
	UINT num_ack;
	// Validate arguments
	if (p == NULL)
	{
		return NULL;
	}

	b = NewBuf();

	// OpCode + KeyID
	uc = ((p->OpCode << 3) & 0xF8) | (p->KeyId & 0x07);
	WriteBufChar(b, uc);

	if (p->OpCode == OPENVPN_P_DATA_V1)
	{
		// Data Packet
		WriteBuf(b, p->Data, p->DataSize);
		SeekBuf(b, 0, 0);
		return b;
	}

	// Sender Channel ID
	WriteBufInt64(b, p->MySessionId);

	// NumAck
	num_ack = MIN(p->NumAck, OPENVPN_MAX_NUMACK);
	WriteBufChar(b, (UCHAR)num_ack);

	if (p->NumAck >= 1)
	{
		UINT i;

		for (i = 0;i < num_ack;i++)
		{
			WriteBufInt(b, (UCHAR)p->AckPacketId[i]);
		}

		// Received Channel ID
		WriteBufInt64(b, p->YourSessionId);
	}

	if (p->OpCode != OPENVPN_P_ACK_V1)
	{
		// Packet ID
		WriteBufInt(b, p->PacketId);

		// Payload
		if (p->DataSize >= 1 && p->Data != NULL)
		{
			WriteBuf(b, p->Data, p->DataSize);
		}
	}

	SeekBuf(b, 0, 0);

	return b;
}