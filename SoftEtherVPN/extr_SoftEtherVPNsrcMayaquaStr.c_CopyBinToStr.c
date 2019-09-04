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

/* Variables and functions */
 int /*<<< orphan*/  BinToStr (char*,int,void*,int) ; 
 char* ZeroMalloc (int) ; 

char *CopyBinToStr(void *data, UINT data_size)
{
	char *ret;
	UINT size;
	// Validate arguments
	if (data == NULL)
	{
		return NULL;
	}

	size = data_size * 2 + 1;
	ret = ZeroMalloc(size);

	BinToStr(ret, size, data, data_size);

	return ret;
}