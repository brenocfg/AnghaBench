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
 int /*<<< orphan*/  BinToStrEx (char*,int,void*,int) ; 
 int /*<<< orphan*/  Free (char*) ; 
 char* Malloc (int) ; 
 int /*<<< orphan*/  Print (char*,char*) ; 

void PrintBin(void *data, UINT size)
{
	char *tmp;
	UINT i;
	// Validate arguments
	if (data == NULL)
	{
		return;
	}

	i = size * 3 + 1;
	tmp = Malloc(i);
	BinToStrEx(tmp, i, data, size);
	Print("%s\n", tmp);
	Free(tmp);
}