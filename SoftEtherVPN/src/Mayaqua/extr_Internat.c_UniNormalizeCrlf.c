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
 int* Malloc (int) ; 
 int UniStrLen (int*) ; 

wchar_t *UniNormalizeCrlf(wchar_t *str)
{
	wchar_t *ret;
	UINT ret_size, i, len, wp;
	// Validate arguments
	if (str == NULL)
	{
		return NULL;
	}

	len = UniStrLen(str);
	ret_size = sizeof(wchar_t) * (len + 32) * 2;
	ret = Malloc(ret_size);

	wp = 0;

	for (i = 0;i < len;i++)
	{
		wchar_t c = str[i];

		switch (c)
		{
		case L'\r':
			if (str[i + 1] == L'\n')
			{
				i++;
			}
			ret[wp++] = L'\r';
			ret[wp++] = L'\n';
			break;

		case L'\n':
			ret[wp++] = L'\r';
			ret[wp++] = L'\n';
			break;

		default:
			ret[wp++] = c;
			break;
		}
	}

	ret[wp++] = 0;

	return ret;
}