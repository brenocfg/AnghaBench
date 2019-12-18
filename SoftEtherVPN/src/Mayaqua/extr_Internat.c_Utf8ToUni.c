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
typedef  scalar_t__ UINT ;
typedef  int BYTE ;

/* Variables and functions */
 scalar_t__ GetUtf8Type (int*,scalar_t__,scalar_t__) ; 
 scalar_t__ IsBigEndian () ; 
 scalar_t__ StrLen (char*) ; 

UINT Utf8ToUni(wchar_t *s, UINT size, BYTE *u, UINT u_size)
{
	UINT i, wp, num;
	// Validate arguments
	if (s == NULL || u == NULL)
	{
		return 0;
	}
	if (size == 0)
	{
		size = 0x3fffffff;
	}
	if (u_size == 0)
	{
		u_size = StrLen((char *)u);
	}

	i = 0;
	wp = 0;
	num = 0;
	while (true)
	{
		UINT type;
		wchar_t c = 0;
		BYTE c1, c2;

		type = GetUtf8Type(u, u_size, i);
		if (type == 0)
		{
			break;
		}
		switch (type)
		{
		case 1:
			c1 = 0;
			c2 = u[i];
			break;
		case 2:
			c1 = (((u[i] & 0x1c) >> 2) & 0x07);
			c2 = (((u[i] & 0x03) << 6) & 0xc0) | (u[i + 1] & 0x3f);
			break;
		case 3:
			c1 = ((((u[i] & 0x0f) << 4) & 0xf0)) | (((u[i + 1] & 0x3c) >> 2) & 0x0f);
			c2 = (((u[i + 1] & 0x03) << 6) & 0xc0) | (u[i + 2] & 0x3f);
			break;
		}
		i += type;

		if (IsBigEndian())
		{
			if (sizeof(wchar_t) == 2)
			{
				((BYTE *)&c)[0] = c1;
				((BYTE *)&c)[1] = c2;
			}
			else
			{
				((BYTE *)&c)[2] = c1;
				((BYTE *)&c)[3] = c2;
			}
		}
		else
		{
			((BYTE *)&c)[0] = c2;
			((BYTE *)&c)[1] = c1;
		}

		if (wp < ((size / sizeof(wchar_t)) - 1))
		{
			s[wp++] = c;
			num++;
		}
		else
		{
			break;
		}
	}

	if (wp < (size / sizeof(wchar_t)))
	{
		s[wp++] = 0;
	}

	return num;
}