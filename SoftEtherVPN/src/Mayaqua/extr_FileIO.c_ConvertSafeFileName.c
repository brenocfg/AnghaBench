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
typedef  size_t UINT ;

/* Variables and functions */
 int IsSafeChar (char) ; 
 int /*<<< orphan*/  StrCpy (char*,size_t,char*) ; 
 size_t StrLen (char*) ; 

void ConvertSafeFileName(char *dst, UINT size, char *src)
{
	UINT i;
	// Validate arguments
	if (dst == NULL || src == NULL)
	{
		return;
	}

	StrCpy(dst, size, src);
	for (i = 0;i < StrLen(dst);i++)
	{
		if (IsSafeChar(dst[i]) == false)
		{
			dst[i] = '_';
		}
	}
}