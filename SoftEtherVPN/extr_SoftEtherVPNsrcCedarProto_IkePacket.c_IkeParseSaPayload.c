#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_8__ {int Size; scalar_t__ Buf; } ;
struct TYPE_7__ {int /*<<< orphan*/  PayloadList; } ;
struct TYPE_6__ {int /*<<< orphan*/  Situation; int /*<<< orphan*/  DoI; } ;
typedef  TYPE_1__ IKE_SA_HEADER ;
typedef  TYPE_2__ IKE_PACKET_SA_PAYLOAD ;
typedef  TYPE_3__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (char*,scalar_t__) ; 
 scalar_t__ Endian32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IKE_PAYLOAD_PROPOSAL ; 
 scalar_t__ IKE_SA_DOI_IPSEC ; 
 scalar_t__ IKE_SA_SITUATION_IDENTITY ; 
 int /*<<< orphan*/  IkeParsePayloadList (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

bool IkeParseSaPayload(IKE_PACKET_SA_PAYLOAD *t, BUF *b)
{
	IKE_SA_HEADER *h;
	UCHAR *buf;
	UINT size;
	// Validate arguments
	if (t == NULL || b == NULL)
	{
		return false;
	}

	if (b->Size < sizeof(IKE_SA_HEADER))
	{
		return false;
	}

	h = (IKE_SA_HEADER *)b->Buf;
	buf = (UCHAR *)b->Buf;
	buf += sizeof(IKE_SA_HEADER);
	size = b->Size - sizeof(IKE_SA_HEADER);

	if (Endian32(h->DoI) != IKE_SA_DOI_IPSEC)
	{
		Debug("ISAKMP: Invalid DoI Value: 0x%x\n", Endian32(h->DoI));
		return false;
	}

	if (Endian32(h->Situation) != IKE_SA_SITUATION_IDENTITY)
	{
		Debug("ISAKMP: Invalid Situation Value: 0x%x\n", Endian32(h->Situation));
		return false;
	}

	t->PayloadList = IkeParsePayloadList(buf, size, IKE_PAYLOAD_PROPOSAL);

	return true;
}