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
typedef  int /*<<< orphan*/  h ;
struct TYPE_6__ {int /*<<< orphan*/  SpiSize; int /*<<< orphan*/  ProtocolId; int /*<<< orphan*/  MessageType; int /*<<< orphan*/  DoI; } ;
struct TYPE_5__ {int /*<<< orphan*/  MessageData; int /*<<< orphan*/ * Spi; int /*<<< orphan*/  ProtocolId; int /*<<< orphan*/  MessageType; } ;
typedef  TYPE_1__ IKE_PACKET_NOTICE_PAYLOAD ;
typedef  TYPE_2__ IKE_NOTICE_HEADER ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (char*,scalar_t__) ; 
 int /*<<< orphan*/  Endian16 (int /*<<< orphan*/ ) ; 
 scalar_t__ Endian32 (int /*<<< orphan*/ ) ; 
 scalar_t__ IKE_SA_DOI_IPSEC ; 
 int ReadBuf (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/ * ReadBufFromBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadRemainBuf (int /*<<< orphan*/ *) ; 

bool IkeParseNoticePayload(IKE_PACKET_NOTICE_PAYLOAD *t, BUF *b)
{
	IKE_NOTICE_HEADER h;
	// Validate arguments
	if (t == NULL || b == NULL)
	{
		return false;
	}

	if (ReadBuf(b, &h, sizeof(h)) != sizeof(h))
	{
		return false;
	}

	if (Endian32(h.DoI) != IKE_SA_DOI_IPSEC)
	{
		Debug("ISAKMP: Invalid DoI Value: 0x%x\n", Endian32(h.DoI));
		return false;
	}

	t->MessageType = Endian16(h.MessageType);
	t->ProtocolId = h.ProtocolId;
	t->Spi = ReadBufFromBuf(b, h.SpiSize);
	if (t->Spi == NULL)
	{
		return false;
	}
	t->MessageData = ReadRemainBuf(b);

	return true;
}