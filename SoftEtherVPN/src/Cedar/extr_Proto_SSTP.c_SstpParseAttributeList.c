#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* USHORT ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_8__ {int TotalLength; } ;
struct TYPE_7__ {void* MessageType; } ;
typedef  TYPE_1__ SSTP_PACKET ;
typedef  TYPE_2__ SSTP_ATTRIBUTE ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 void* READ_USHORT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SstpFreeAttribute (TYPE_2__*) ; 
 int /*<<< orphan*/  SstpFreeAttributeList (int /*<<< orphan*/ *) ; 
 TYPE_2__* SstpParseAttribute (int /*<<< orphan*/ *,int) ; 

LIST *SstpParseAttributeList(UCHAR *data, UINT size, SSTP_PACKET *p)
{
	LIST *o;
	USHORT us;
	UINT num;
	// Validate arguments
	if (size == 0 || data == NULL || p == NULL)
	{
		return NULL;
	}

	if (size < 4)
	{
		return NULL;
	}

	// Message Type
	us = READ_USHORT(data);
	p->MessageType = us;
	data += sizeof(USHORT);
	size -= sizeof(USHORT);

	// Num Attributes
	num = READ_USHORT(data);
	data += sizeof(USHORT);
	size -= sizeof(USHORT);

	// Attributes List
	o = NewListFast(NULL);

	while (LIST_NUM(o) < num)
	{
		SSTP_ATTRIBUTE *a = SstpParseAttribute(data, size);

		if (a == NULL)
		{
			SstpFreeAttributeList(o);
			return NULL;
		}

		if (a->TotalLength > size)
		{
			SstpFreeAttribute(a);
			SstpFreeAttributeList(o);
			return NULL;
		}

		Add(o, a);

		data += a->TotalLength;
		size -= a->TotalLength;
	}

	return o;
}