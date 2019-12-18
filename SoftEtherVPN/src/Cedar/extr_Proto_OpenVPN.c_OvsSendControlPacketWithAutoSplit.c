#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/  OPENVPN_CHANNEL ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewBuf () ; 
 int OPENVPN_CONTROL_PACKET_MAX_DATASIZE ; 
 int /*<<< orphan*/  OvsSendControlPacket (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ReadBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SeekBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

void OvsSendControlPacketWithAutoSplit(OPENVPN_CHANNEL *c, UCHAR opcode, UCHAR *data, UINT data_size)
{
	BUF *b;
	// Validate arguments
	if (c == NULL || (data_size != 0 && data == NULL))
	{
		return;
	}

	b = NewBuf();
	WriteBuf(b, data, data_size);
	SeekBuf(b, 0, 0);

	while (true)
	{
		UCHAR tmp[OPENVPN_CONTROL_PACKET_MAX_DATASIZE];
		UINT size = ReadBuf(b, tmp, sizeof(tmp));

		if (size == 0)
		{
			break;
		}

		OvsSendControlPacket(c, opcode, tmp, size);
		//Debug(" *** CNT SEND %u\n", size);
	}

	FreeBuf(b);
}