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
typedef  int UINT ;
typedef  int UCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  Free (void**) ; 
 int /*<<< orphan*/  InputToNull (void*) ; 
 void* ReAlloc (void*,int) ; 
 void* ZeroMalloc (int) ; 

bool CheckMemory()
{
	UINT i, num, size, j;
	void **pp;
	bool ok = true;
	UINT old_size;

	num = 2000;
	size = 1000;
	pp = ZeroMalloc(sizeof(void *) * num);
	for (i = 0;i < num;i++)
	{
		pp[i] = ZeroMalloc(size);
		InputToNull(pp[i]);
		for (j = 0;j < size;j++)
		{
			((UCHAR *)pp[i])[j] = j % 256;
		}
	}
	old_size = size;
	size = size * 3;
	for (i = 0;i < num;i++)
	{
		pp[i] = ReAlloc(pp[i], size);
		for (j = old_size;j < size;j++)
		{
			InputToNull((void *)(UINT)(((UCHAR *)pp[i])[j] = j % 256));
		}
	}
	for (i = 0;i < num;i++)
	{
		for (j = 0;j < size;j++)
		{
			if (((UCHAR *)pp[i])[j] != (j % 256))
			{
				ok = false;
			}
		}
		Free(pp[i]);
	}
	Free(pp);

	return ok;
}