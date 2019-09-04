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
typedef  scalar_t__ USHORT ;
typedef  scalar_t__ UCHAR ;
struct TYPE_3__ {int TotalLength; int DataSize; scalar_t__* Data; scalar_t__ AttributeId; } ;
typedef  TYPE_1__ SSTP_ATTRIBUTE ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 scalar_t__ Endian16 (scalar_t__) ; 
 int /*<<< orphan*/ * NewBuf () ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,scalar_t__*,int) ; 

BUF *SstpBuildAttribute(SSTP_ATTRIBUTE *a)
{
	UCHAR uc;
	USHORT us;
	BUF *b;
	// Validate arguments
	if (a == NULL)
	{
		return NULL;
	}

	b = NewBuf();

	// Reserved
	uc = 0;
	WriteBuf(b, &uc, sizeof(UCHAR));

	// Attribute ID
	uc = a->AttributeId;
	WriteBuf(b, &uc, sizeof(UCHAR));

	// LengthPacket
	a->TotalLength = a->DataSize + 4;
	us = (USHORT)a->TotalLength;
	us = Endian16(us);
	WriteBuf(b, &us, sizeof(USHORT));

	// Data
	WriteBuf(b, a->Data, a->DataSize);

	return b;
}