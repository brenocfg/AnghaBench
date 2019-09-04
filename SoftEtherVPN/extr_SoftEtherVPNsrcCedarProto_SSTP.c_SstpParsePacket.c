#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int USHORT ;
typedef  int UINT ;
typedef  int UCHAR ;
struct TYPE_6__ {int Version; int IsControl; int DataSize; int /*<<< orphan*/ * AttributeList; int /*<<< orphan*/  Data; } ;
typedef  TYPE_1__ SSTP_PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  Clone (int*,int) ; 
 int READ_USHORT (int*) ; 
 scalar_t__ SSTP_VERSION_1 ; 
 int /*<<< orphan*/  SstpFreePacket (TYPE_1__*) ; 
 int /*<<< orphan*/ * SstpParseAttributeList (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 TYPE_1__* ZeroMalloc (int) ; 

SSTP_PACKET *SstpParsePacket(UCHAR *data, UINT size)
{
	SSTP_PACKET *p;
	USHORT len;
	// Validate arguments
	if (data == NULL || size == 0)
	{
		return NULL;
	}

	if (size < 4)
	{
		return NULL;
	}

	p = ZeroMalloc(sizeof(SSTP_PACKET));

	// Version
	p->Version = *((UCHAR *)data);
	data++;
	size--;

	if (p->Version != SSTP_VERSION_1)
	{
		// Invalid version
		SstpFreePacket(p);
		return NULL;
	}

	// Flag
	if ((*((UCHAR *)data)) & 0x01)
	{
		p->IsControl = true;
	}
	data++;
	size--;

	// Length
	len = READ_USHORT(data) & 0xFFF;
	data += sizeof(USHORT);
	size -= sizeof(USHORT);

	if (len < 4)
	{
		// Invalid size
		SstpFreePacket(p);
		return NULL;
	}

	if (((UINT)(len - 4)) > size)
	{
		// Oversized
		SstpFreePacket(p);
		return NULL;
	}

	// Data
	p->DataSize = len - 4;
	p->Data = Clone(data, p->DataSize);

	if (p->IsControl)
	{
		// Parse the Attribute list
		p->AttributeList = SstpParseAttributeList(p->Data, p->DataSize, p);

		if (p->AttributeList == NULL)
		{
			// Failure of parsing list
			SstpFreePacket(p);
			return NULL;
		}
	}

	return p;
}