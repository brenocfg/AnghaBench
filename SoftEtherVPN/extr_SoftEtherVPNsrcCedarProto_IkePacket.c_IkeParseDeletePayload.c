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
typedef  int /*<<< orphan*/  h ;
typedef  scalar_t__ UINT ;
struct TYPE_7__ {scalar_t__ SpiSize; int /*<<< orphan*/  NumSpis; int /*<<< orphan*/  ProtocolId; int /*<<< orphan*/  DoI; } ;
struct TYPE_6__ {int /*<<< orphan*/  SpiList; int /*<<< orphan*/  ProtocolId; } ;
typedef  TYPE_1__ IKE_PACKET_DELETE_PAYLOAD ;
typedef  TYPE_2__ IKE_DELETE_HEADER ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Debug (char*,scalar_t__) ; 
 scalar_t__ Endian16 (int /*<<< orphan*/ ) ; 
 scalar_t__ Endian32 (int /*<<< orphan*/ ) ; 
 scalar_t__ IKE_SA_DOI_IPSEC ; 
 int /*<<< orphan*/  IkeFreeDeletePayload (TYPE_1__*) ; 
 int /*<<< orphan*/  NewListFast (int /*<<< orphan*/ *) ; 
 int ReadBuf (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/ * ReadBufFromBuf (int /*<<< orphan*/ *,scalar_t__) ; 

bool IkeParseDeletePayload(IKE_PACKET_DELETE_PAYLOAD *t, BUF *b)
{
	IKE_DELETE_HEADER h;
	UINT num_spi;
	UINT spi_size;
	UINT i;
	bool ok = true;
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

	t->ProtocolId = h.ProtocolId;
	t->SpiList = NewListFast(NULL);
	num_spi = Endian16(h.NumSpis);
	spi_size = h.SpiSize;

	for (i = 0;i < num_spi;i++)
	{
		BUF *spi = ReadBufFromBuf(b, spi_size);

		if (spi == NULL)
		{
			ok = false;
			break;
		}

		Add(t->SpiList, spi);
	}

	if (ok == false)
	{
		IkeFreeDeletePayload(t);
		return false;
	}

	return true;
}