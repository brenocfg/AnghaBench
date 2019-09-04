#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_17__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_16__ {int /*<<< orphan*/  PayloadList; } ;
struct TYPE_13__ {TYPE_10__* Data; } ;
struct TYPE_14__ {TYPE_1__ VendorId; } ;
struct TYPE_15__ {TYPE_2__ Payload; } ;
struct TYPE_12__ {int /*<<< orphan*/  Buf; int /*<<< orphan*/  Size; } ;
typedef  TYPE_3__ IKE_PACKET_PAYLOAD ;
typedef  TYPE_4__ IKE_PACKET ;
typedef  TYPE_5__ BUF ;

/* Variables and functions */
 scalar_t__ Cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CompareBuf (TYPE_10__*,TYPE_5__*) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_5__*) ; 
 int /*<<< orphan*/  IKE_PAYLOAD_VENDOR_ID ; 
 TYPE_3__* IkeGetPayload (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ IkeGetPayloadNum (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* IkeStrToVendorId (char*) ; 

bool IkeIsVendorIdExists(IKE_PACKET *p, char *str)
{
	BUF *buf;
	UINT i, num;
	bool ok = false;
	// Validate arguments
	if (p == NULL || str == NULL)
	{
		return false;
	}

	buf = IkeStrToVendorId(str);
	if (buf == NULL)
	{
		return false;
	}

	num = IkeGetPayloadNum(p->PayloadList, IKE_PAYLOAD_VENDOR_ID);
	for (i = 0;i < num;i++)
	{
		IKE_PACKET_PAYLOAD *payload = IkeGetPayload(p->PayloadList, IKE_PAYLOAD_VENDOR_ID, i);
		if (payload == NULL)
		{
			return false;
		}

		if (CompareBuf(payload->Payload.VendorId.Data, buf))
		{
			ok = true;
		}
		else
		{
			if (payload->Payload.VendorId.Data != NULL)
			{
				if (payload->Payload.VendorId.Data->Size >= buf->Size)
				{
					if (Cmp(payload->Payload.VendorId.Data->Buf, buf->Buf, buf->Size) == 0)
					{
						ok = true;
					}
				}
			}
		}
	}

	FreeBuf(buf);

	return ok;
}