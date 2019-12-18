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
typedef  char wchar_t ;
typedef  size_t UINT ;

/* Variables and functions */
 size_t UniStrLen (char*) ; 

void UniSafeFileName(wchar_t *name)
{
	UINT i, len, dlen;
	static wchar_t *danger_str = L"\\/:*?\"<>|";
	// Validate arguments
	if (name == NULL)
	{
		return;
	}

	dlen = UniStrLen(danger_str);
	len = UniStrLen(name);

	for (i = 0;i < len;i++)
	{
		wchar_t c = name[i];
		UINT j;
		for (j = 0;j < dlen;j++)
		{
			if (c == danger_str[j])
			{
				c = L'_';
			}
		}
		name[i] = c;
	}
}