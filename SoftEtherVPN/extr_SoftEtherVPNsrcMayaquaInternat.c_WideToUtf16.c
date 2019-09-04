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
typedef  scalar_t__ wchar_t ;
typedef  scalar_t__ USHORT ;
typedef  int UINT ;

/* Variables and functions */
 scalar_t__* Malloc (int) ; 
 int UniStrLen (scalar_t__*) ; 

USHORT *WideToUtf16(wchar_t *str)
{
	USHORT *ret;
	UINT len;
	UINT ret_size;
	UINT i;
	// Validate arguments
	if (str == NULL)
	{
		return NULL;
	}

	len = UniStrLen(str);

	ret_size = (len + 1) * 2;
	ret = Malloc(ret_size);

	for (i = 0;i < len + 1;i++)
	{
		ret[i] = (USHORT)str[i];
	}

	return ret;
}