#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USHORT ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_5__ {int TotalLength; int DataSize; int /*<<< orphan*/  Data; int /*<<< orphan*/  AttributeId; } ;
typedef  TYPE_1__ SSTP_ATTRIBUTE ;

/* Variables and functions */
 int /*<<< orphan*/  Clone (int /*<<< orphan*/ *,int) ; 
 int READ_USHORT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SstpFreeAttribute (TYPE_1__*) ; 
 TYPE_1__* ZeroMalloc (int) ; 

SSTP_ATTRIBUTE *SstpParseAttribute(UCHAR *data, UINT size)
{
	SSTP_ATTRIBUTE *a;
	// Validate arguments
	if (data == NULL || size == 0)
	{
		return NULL;
	}

	a = ZeroMalloc(sizeof(SSTP_ATTRIBUTE));

	if (size < 4)
	{
		SstpFreeAttribute(a);
		return NULL;
	}

	data++;
	size--;

	// Attribute ID
	a->AttributeId = *((UCHAR *)data);
	data++;
	size--;

	// Length
	a->TotalLength = READ_USHORT(data) & 0xFFF;
	data += sizeof(USHORT);
	size -= sizeof(USHORT);

	if (a->TotalLength < 4)
	{
		// Length fraud
		SstpFreeAttribute(a);
		return NULL;
	}

	a->DataSize = a->TotalLength - 4;
	if (a->DataSize > size)
	{
		// Length excess
		SstpFreeAttribute(a);
		return NULL;
	}

	a->Data = Clone(data, a->DataSize);

	return a;
}