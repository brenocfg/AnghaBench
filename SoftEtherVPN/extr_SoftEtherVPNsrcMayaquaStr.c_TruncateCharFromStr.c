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

/* Variables and functions */

void TruncateCharFromStr(char *str, char replace)
{
	char *src,*dst;

	if (str == NULL)
	{
		return;
	}

	src = dst = str;

	while(*src != '\0')
	{
		if(*src != replace)
		{
			*dst = *src;
			dst++;
		}
		src++;
	}
	*dst = *src;

	//BUF *b = NewBuf();
	//UINT i, len;
	//char zero = 0;

	//len = StrLen(str);
	//for (i = 0;i < len;i++)
	//{
	//	char c = str[i];

	//	if (c != replace)
	//	{
	//		WriteBuf(b, &c, 1);
	//	}
	//}

	//if (b->Size == 0)
	//{
	//	char c = '_';
	//	WriteBuf(b, &c, 1);
	//}

	//WriteBuf(b, &zero, 1);

	//StrCpy(str, 0, b->Buf);

	//FreeBuf(b);
}