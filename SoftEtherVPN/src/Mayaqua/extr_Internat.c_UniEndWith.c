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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  scalar_t__ UINT ;

/* Variables and functions */
 scalar_t__ UniStrCmpi (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ UniStrLen (int /*<<< orphan*/ *) ; 

bool UniEndWith(wchar_t *str, wchar_t *key)
{
	UINT str_len;
	UINT key_len;
	// Validate arguments
	if (str == NULL || key == NULL)
	{
		return false;
	}

	// Comparison
	str_len = UniStrLen(str);
	key_len = UniStrLen(key);
	if (str_len < key_len)
	{
		return false;
	}

	if (UniStrCmpi(str + (str_len - key_len), key) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}