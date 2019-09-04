#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int USHORT ;
typedef  int UCHAR ;
struct TYPE_4__ {int Id; int Size; int /*<<< orphan*/  Data; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ DHCP_OPTION ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  Clone (int*,int) ; 
 int Endian16 (int) ; 
 int /*<<< orphan*/ * NewList (int /*<<< orphan*/ *) ; 
 int ReadBuf (int /*<<< orphan*/ *,int*,int) ; 
 TYPE_1__* ZeroMalloc (int) ; 

LIST *RadiusParseOptions(BUF *b)
{
	LIST *o;
	UCHAR code;
	UCHAR id;
	USHORT len;
	UCHAR auth[16];
	// Validate arguments
	if (b == NULL)
	{
		return NULL;
	}

	o = NewList(NULL);

	ReadBuf(b, &code, 1);
	ReadBuf(b, &id, 1);
	len = 0;
	ReadBuf(b, &len, 2);
	len = Endian16(len);
	ReadBuf(b, auth, 16);

	while (true)
	{
		UCHAR attribute_id;
		UCHAR size;
		UCHAR data[256];
		DHCP_OPTION *d;

		if (ReadBuf(b, &attribute_id, 1) != 1)
		{
			break;
		}

		if (ReadBuf(b, &size, 1) != 1)
		{
			break;
		}

		if (size <= 2)
		{
			break;
		}

		size -= 2;
		if (ReadBuf(b, data, size) != size)
		{
			break;
		}

		d = ZeroMalloc(sizeof(DHCP_OPTION));
		d->Id = attribute_id;
		d->Size = size;
		d->Data = Clone(data, d->Size);

		Add(o, d);
	}

	return o;
}