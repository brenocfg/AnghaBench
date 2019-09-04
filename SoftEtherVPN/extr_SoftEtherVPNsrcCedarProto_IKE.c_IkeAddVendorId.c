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
struct TYPE_7__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_6__ {int /*<<< orphan*/  PayloadList; } ;
typedef  int /*<<< orphan*/  IKE_PACKET_PAYLOAD ;
typedef  TYPE_1__ IKE_PACKET ;
typedef  TYPE_2__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_2__*) ; 
 int /*<<< orphan*/  IKE_PAYLOAD_VENDOR_ID ; 
 int /*<<< orphan*/ * IkeNewDataPayload (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* IkeStrToVendorId (char*) ; 

void IkeAddVendorId(IKE_PACKET *p, char *str)
{
	BUF *buf;
	IKE_PACKET_PAYLOAD *payload;
	// Validate arguments
	if (p == NULL || str == NULL)
	{
		return;
	}

	buf = IkeStrToVendorId(str);
	if (buf == NULL)
	{
		return;
	}

	payload = IkeNewDataPayload(IKE_PAYLOAD_VENDOR_ID, buf->Buf, buf->Size);

	Add(p->PayloadList, payload);

	FreeBuf(buf);
}