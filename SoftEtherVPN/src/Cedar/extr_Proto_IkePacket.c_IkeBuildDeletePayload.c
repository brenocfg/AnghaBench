#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h ;
typedef  int UINT ;
struct TYPE_13__ {int Size; TYPE_2__* Buf; } ;
struct TYPE_12__ {int SpiSize; int /*<<< orphan*/  ProtocolId; int /*<<< orphan*/  NumSpis; int /*<<< orphan*/  DoI; } ;
struct TYPE_11__ {int /*<<< orphan*/  SpiList; int /*<<< orphan*/  ProtocolId; } ;
typedef  TYPE_1__ IKE_PACKET_DELETE_PAYLOAD ;
typedef  TYPE_2__ IKE_DELETE_HEADER ;
typedef  TYPE_3__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Endian16 (int) ; 
 int /*<<< orphan*/  Endian32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IKE_SA_DOI_IPSEC ; 
 TYPE_3__* LIST_DATA (int /*<<< orphan*/ ,int) ; 
 int LIST_NUM (int /*<<< orphan*/ ) ; 
 TYPE_3__* NewBuf () ; 
 int /*<<< orphan*/  WriteBuf (TYPE_3__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

BUF *IkeBuildDeletePayload(IKE_PACKET_DELETE_PAYLOAD *t)
{
	IKE_DELETE_HEADER h;
	BUF *ret;
	UINT i;
	// Validate arguments
	if (t == NULL)
	{
		return NULL;
	}

	Zero(&h, sizeof(h));
	h.DoI = Endian32(IKE_SA_DOI_IPSEC);
	h.NumSpis = Endian16(LIST_NUM(t->SpiList));
	h.ProtocolId = t->ProtocolId;

	if (LIST_NUM(t->SpiList) >= 1)
	{
		BUF *b = LIST_DATA(t->SpiList, 0);

		h.SpiSize = b->Size;
	}

	ret = NewBuf();
	WriteBuf(ret, &h, sizeof(h));

	for (i = 0;i < LIST_NUM(t->SpiList);i++)
	{
		BUF *b = LIST_DATA(t->SpiList, i);

		WriteBuf(ret, b->Buf, b->Size);
	}

	return ret;
}