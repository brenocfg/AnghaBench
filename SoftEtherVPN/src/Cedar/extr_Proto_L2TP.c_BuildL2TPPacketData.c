#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int USHORT ;
typedef  scalar_t__ UINT ;
typedef  int UCHAR ;
struct TYPE_18__ {int Size; scalar_t__ Buf; } ;
struct TYPE_17__ {int DataSize; int VendorID; int Type; int* Data; scalar_t__ Mandatory; } ;
struct TYPE_16__ {int Ver; scalar_t__ SessionId; int IsControl; scalar_t__ TunnelId; int Ns; int Nr; int* Data; int DataSize; int /*<<< orphan*/  AvpList; } ;
struct TYPE_15__ {int IsYamahaV3; } ;
typedef  TYPE_1__ L2TP_TUNNEL ;
typedef  TYPE_2__ L2TP_PACKET ;
typedef  TYPE_3__ L2TP_AVP ;
typedef  TYPE_4__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int Endian16 (int) ; 
 scalar_t__ Endian32 (scalar_t__) ; 
 TYPE_3__* GetAVPValue (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GetAVPValueEx (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L2TPV3_CISCO_AVP_SESSION_ID_LOCAL ; 
 int /*<<< orphan*/  L2TPV3_CISCO_AVP_SESSION_ID_REMOTE ; 
 int L2TP_AVP_BIT_MANDATORY ; 
 int /*<<< orphan*/  L2TP_AVP_TYPE_V3_SESSION_ID_REMOTE ; 
 int /*<<< orphan*/  L2TP_AVP_VENDOR_ID_CISCO ; 
 int L2TP_HEADER_BIT_LENGTH ; 
 int L2TP_HEADER_BIT_OFFSET ; 
 int L2TP_HEADER_BIT_SEQUENCE ; 
 int L2TP_HEADER_BIT_TYPE ; 
 TYPE_3__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NewAVP (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 TYPE_4__* NewBuf () ; 
 int /*<<< orphan*/  SeekBuf (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_USHORT (int*,int) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_4__*,...) ; 

BUF *BuildL2TPPacketData(L2TP_PACKET *pp, L2TP_TUNNEL *t)
{
	BUF *ret;
	UCHAR c;
	USHORT us;
	UINT ui;
	// Validate arguments
	if (pp == NULL || t == NULL)
	{
		return NULL;
	}

	ret = NewBuf();

	c = 0;

	if (pp->Ver == 3)
	{
		if (pp->SessionId != 0)
		{
			// Add the Remote Session ID AVP
			L2TP_AVP *a = GetAVPValue(pp, L2TP_AVP_TYPE_V3_SESSION_ID_REMOTE);
			if (a == NULL || a->DataSize != sizeof(UINT))
			{
				UINT ui = Endian32(pp->SessionId);
				Add(pp->AvpList, NewAVP(L2TP_AVP_TYPE_V3_SESSION_ID_REMOTE, true, 0, &ui, sizeof(UINT)));

				if (GetAVPValueEx(pp, L2TPV3_CISCO_AVP_SESSION_ID_LOCAL, L2TP_AVP_VENDOR_ID_CISCO) != NULL)
				{
					Add(pp->AvpList, NewAVP(L2TPV3_CISCO_AVP_SESSION_ID_REMOTE, true, L2TP_AVP_VENDOR_ID_CISCO, &ui, sizeof(UINT)));
				}
			}
		}
	}

	if (pp->Ver == 3)
	{
		if (t->IsYamahaV3 == false)
		{
			// Zero as Session ID
			ui = 0;
			WriteBuf(ret, &ui, sizeof(UINT));
		}
	}

	// Flags
	if (pp->IsControl)
	{
		c |= L2TP_HEADER_BIT_TYPE;
		c |= L2TP_HEADER_BIT_LENGTH;
		c |= L2TP_HEADER_BIT_SEQUENCE;
	}
	else
	{
		c |= L2TP_HEADER_BIT_OFFSET;
	}

	if (pp->IsControl == false && pp->Ver == 3 && t->IsYamahaV3)
	{
		c = 0;
	}

	WriteBuf(ret, &c, 1);

	// Ver
	c = 2;
	if (pp->Ver == 3)
	{
		c = 3;
	}
	WriteBuf(ret, &c, 1);

	// Length
	if (pp->IsControl)
	{
		us = 0;
		WriteBuf(ret, &us, sizeof(USHORT));
	}

	// Reserved
	if (pp->IsControl == false && pp->Ver == 3 && t->IsYamahaV3)
	{
		us = 0;
		WriteBuf(ret, &us, sizeof(USHORT));
	}

	// Tunnel ID
	if (pp->Ver != 3)
	{
		us = Endian16((USHORT)pp->TunnelId);
		WriteBuf(ret, &us, sizeof(USHORT));
	}
	else
	{
		ui = Endian32(pp->TunnelId);
		WriteBuf(ret, &ui, sizeof(UINT));
	}

	// Session ID
	if (pp->Ver != 3)
	{
		us = Endian16((USHORT)pp->SessionId);
		WriteBuf(ret, &us, sizeof(USHORT));
	}

	if (pp->IsControl)
	{
		// Ns
		us = Endian16(pp->Ns);
		WriteBuf(ret, &us, sizeof(USHORT));

		// Nr
		us = Endian16(pp->Nr);
		WriteBuf(ret, &us, sizeof(USHORT));
	}
	else
	{
		if (!(pp->IsControl == false && pp->Ver == 3 && t->IsYamahaV3))
		{
			// Offset Size = 0
			us = 0;
			WriteBuf(ret, &us, sizeof(USHORT));
		}
	}

	if (pp->IsControl)
	{
		// AVP
		UINT i;
		for (i = 0;i < LIST_NUM(pp->AvpList);i++)
		{
			L2TP_AVP *a = LIST_DATA(pp->AvpList, i);

			// Length and Flags
			us = Endian16(a->DataSize + 6);

			if (a->Mandatory)
			{
				*((UCHAR *)&us) |= L2TP_AVP_BIT_MANDATORY;
			}

			WriteBuf(ret, &us, sizeof(USHORT));

			// Vendor ID
			us = Endian16(a->VendorID);
			WriteBuf(ret, &us, sizeof(USHORT));

			// Type
			us = Endian16(a->Type);
			WriteBuf(ret, &us, sizeof(USHORT));

			// Data
			WriteBuf(ret, a->Data, a->DataSize);
		}
	}
	else
	{
		// Payload
		WriteBuf(ret, pp->Data, pp->DataSize);
	}

	if (pp->IsControl)
	{
		// Update Length
		bool l2tpv3_non_yamaha = ((pp->Ver == 3) && (t->IsYamahaV3 == false));
		WRITE_USHORT(((UCHAR *)ret->Buf) + 2 + (l2tpv3_non_yamaha ? sizeof(UINT) : 0), (USHORT)(ret->Size - (l2tpv3_non_yamaha ? sizeof(UINT) : 0)));
	}

	SeekBuf(ret, 0, 0);

	return ret;
}