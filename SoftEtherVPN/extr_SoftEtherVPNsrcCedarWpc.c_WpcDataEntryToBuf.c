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
struct TYPE_3__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Data; } ;
typedef  TYPE_1__ WPC_ENTRY ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 scalar_t__ DecodeSafe64 (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (void*) ; 
 void* Malloc (scalar_t__) ; 
 int /*<<< orphan*/ * NewBuf () ; 
 int /*<<< orphan*/  SeekBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,void*,scalar_t__) ; 

BUF *WpcDataEntryToBuf(WPC_ENTRY *e)
{
	void *data;
	UINT data_size;
	UINT size;
	BUF *b;
	// Validate arguments
	if (e == NULL)
	{
		return NULL;
	}

	data_size = e->Size + 4096;
	data = Malloc(data_size);
	size = DecodeSafe64(data, e->Data, e->Size);

	b = NewBuf();
	WriteBuf(b, data, size);
	SeekBuf(b, 0, 0);

	Free(data);

	return b;
}