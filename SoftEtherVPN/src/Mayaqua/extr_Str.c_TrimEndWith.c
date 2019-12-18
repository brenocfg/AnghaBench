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
typedef  scalar_t__ UINT ;

/* Variables and functions */
 int /*<<< orphan*/  ClearStr (char*,scalar_t__) ; 
 scalar_t__ EndWith (char*,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,scalar_t__,char*) ; 
 scalar_t__ StrLen (char*) ; 

bool TrimEndWith(char *dst, UINT dst_size, char *str, char *key)
{
	if (dst == NULL || str == NULL)
	{
		ClearStr(dst, dst_size);
		return false;
	}

	StrCpy(dst, dst_size, str);

	if (EndWith(str, key))
	{
		UINT src_len = StrLen(str);
		UINT key_len = StrLen(key);

		if (src_len >= key_len)
		{
			dst[src_len - key_len] = 0;
		}

		return true;
	}

	return false;
}