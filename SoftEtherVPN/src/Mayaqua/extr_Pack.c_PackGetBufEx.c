#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Free (void*) ; 
 void* MallocEx (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * NewBuf () ; 
 int PackGetDataEx (int /*<<< orphan*/ *,char*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackGetDataSizeEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SeekBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 

BUF *PackGetBufEx(PACK *p, char *name, UINT index)
{
	UINT size;
	void *tmp;
	BUF *b;
	// Validate arguments
	if (p == NULL || name == NULL)
	{
		return NULL;
	}

	size = PackGetDataSizeEx(p, name, index);
	tmp = MallocEx(size, true);
	if (PackGetDataEx(p, name, tmp, index) == false)
	{
		Free(tmp);
		return NULL;
	}

	b = NewBuf();
	WriteBuf(b, tmp, size);
	SeekBuf(b, 0, 0);

	Free(tmp);

	return b;
}