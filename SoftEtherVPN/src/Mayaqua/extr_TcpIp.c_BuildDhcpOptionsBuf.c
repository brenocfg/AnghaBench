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
typedef  scalar_t__ UINT ;
typedef  scalar_t__ UCHAR ;
struct TYPE_3__ {scalar_t__ Size; scalar_t__* Data; scalar_t__ Id; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ DHCP_OPTION ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 scalar_t__ DHCP_ID_PRIVATE ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewBuf () ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,scalar_t__*,int) ; 

BUF *BuildDhcpOptionsBuf(LIST *o)
{
	BUF *b;
	UINT i;
	UCHAR id;
	UCHAR sz;
	// Validate arguments
	if (o == NULL)
	{
		return NULL;
	}

	b = NewBuf();
	for (i = 0;i < LIST_NUM(o);i++)
	{
		DHCP_OPTION *d = LIST_DATA(o, i);
		UINT current_size = d->Size;
		UINT current_pos = 0;

		id = (UCHAR)d->Id;
		if (d->Size <= 255)
		{
			sz = (UCHAR)d->Size;
		}
		else
		{
			sz = 0xFF;
		}
		WriteBuf(b, &id, 1);
		WriteBuf(b, &sz, 1);
		WriteBuf(b, d->Data, sz);

		current_size -= sz;
		current_pos += sz;

		while (current_size != 0)
		{
			id = DHCP_ID_PRIVATE;
			if (current_size <= 255)
			{
				sz = (UCHAR)current_size;
			}
			else
			{
				sz = 0xFF;
			}
			WriteBuf(b, &id, 1);
			WriteBuf(b, &sz, 1);
			WriteBuf(b, ((UCHAR *)d->Data) + current_pos, sz);

			current_size -= sz;
			current_pos += sz;
		}

	}

	id = 0xff;
	WriteBuf(b, &id, 1);

	return b;
}