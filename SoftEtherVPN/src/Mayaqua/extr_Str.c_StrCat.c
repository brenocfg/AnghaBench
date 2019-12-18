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
 int /*<<< orphan*/  Copy (char*,char*,int) ; 
 int /*<<< orphan*/  KS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KS_STRCAT_COUNT ; 
 int StrLen (char*) ; 

UINT StrCat(char *dst, UINT size, char *src)
{
	UINT len1, len2, len_test;
	// Validate arguments
	if (dst == NULL || src == NULL)
	{
		return 0;
	}

	// KS
	KS_INC(KS_STRCAT_COUNT);

	if (size == 0)
	{
		// Ignore the length
		size = 0x7fffffff;
	}

	len1 = StrLen(dst);
	len2 = StrLen(src);
	len_test = len1 + len2 + 1;
	if (len_test > size)
	{
		if (len2 <= (len_test - size))
		{
			return 0;
		}
		len2 -= len_test - size;
	}
	Copy(dst + len1, src, len2);
	dst[len1 + len2] = 0;

	return len1 + len2;
}