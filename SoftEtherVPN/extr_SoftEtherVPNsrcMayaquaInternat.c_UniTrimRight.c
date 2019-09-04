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
typedef  int wchar_t ;
typedef  int UINT ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int*,int*,int) ; 
 int /*<<< orphan*/  Free (int*) ; 
 int* Malloc (int) ; 
 int /*<<< orphan*/  UniStrCpy (int*,int /*<<< orphan*/ ,int*) ; 
 int UniStrLen (int*) ; 

void UniTrimRight(wchar_t *str)
{
	wchar_t *buf, *tmp;
	UINT len, i, wp, wp2;
	bool flag;
	// Validate arguments
	if (str == NULL)
	{
		return;
	}
	len = UniStrLen(str);
	if (len == 0)
	{
		return;
	}
	if (str[len - 1] != L' ' && str[len - 1] != L'\t')
	{
		return;
	}

	buf = Malloc((len + 1) * sizeof(wchar_t));
	tmp = Malloc((len + 1) * sizeof(wchar_t));
	flag = false;
	wp = wp2 = 0;
	for (i = 0;i < len;i++)
	{
		if (str[i] != L' ' && str[i] != L'\t')
		{
			Copy(&buf[wp], tmp, wp2 * sizeof(wchar_t));
			wp += wp2;
			wp2 = 0;
			buf[wp++] = str[i];
		}
		else
		{
			tmp[wp2++] = str[i];
		}
	}
	buf[wp] = 0;
	UniStrCpy(str, 0, buf);
	Free(buf);
	Free(tmp);
}