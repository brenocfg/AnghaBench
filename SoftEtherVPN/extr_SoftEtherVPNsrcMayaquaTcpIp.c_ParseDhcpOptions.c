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
typedef  int UINT ;
typedef  int UCHAR ;
struct TYPE_3__ {int Size; int* Data; int Id; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ DHCP_OPTION ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  Copy (int*,int*,int) ; 
 int DHCP_ID_PRIVATE ; 
 int /*<<< orphan*/  Free (int*) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewBuf () ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int ReadBuf (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  SeekBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,void*,int) ; 
 void* ZeroMalloc (int) ; 

LIST *ParseDhcpOptions(void *data, UINT size)
{
	BUF *b;
	LIST *o;
	DHCP_OPTION *last_opt;
	// Validate arguments
	if (data == NULL)
	{
		return NULL;
	}

	b = NewBuf();
	WriteBuf(b, data, size);
	SeekBuf(b, 0, 0);

	o = NewListFast(NULL);

	last_opt = NULL;

	while (true)
	{
		UCHAR c = 0;
		UCHAR sz = 0;
		DHCP_OPTION *opt;
		if (ReadBuf(b, &c, 1) != 1)
		{
			break;
		}
		if (c == 0xff)
		{
			break;
		}
		if (ReadBuf(b, &sz, 1) != 1)
		{
			break;
		}

		if (c == DHCP_ID_PRIVATE && last_opt != NULL)
		{
			UINT new_size = last_opt->Size + (UINT)sz;
			UCHAR *new_buf = ZeroMalloc(new_size);
			Copy(new_buf, last_opt->Data, last_opt->Size);
			ReadBuf(b, new_buf + last_opt->Size, sz);
			Free(last_opt->Data);
			last_opt->Data = new_buf;
			last_opt->Size = new_size;
		}
		else
		{
			opt = ZeroMalloc(sizeof(DHCP_OPTION));
			opt->Id = (UINT)c;
			opt->Size = (UINT)sz;
			opt->Data = ZeroMalloc((UINT)sz);
			ReadBuf(b, opt->Data, sz);
			Add(o, opt);

			last_opt = opt;
		}
	}

	FreeBuf(b);

	return o;
}