#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
typedef  char UCHAR ;
struct TYPE_5__ {int /*<<< orphan*/  Buf; } ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 char* CopyStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_1__*) ; 
 size_t HexToInt (char*) ; 
 TYPE_1__* NewBuf () ; 
 size_t StrLen (char*) ; 
 int /*<<< orphan*/  WriteBufChar (TYPE_1__*,char) ; 

char *UrlDecode(char *url_str)
{
	UINT i, len;
	BUF *b;
	char *ret;
	if (url_str == NULL)
	{
		return NULL;
	}

	len = StrLen(url_str);

	b = NewBuf();

	for (i = 0;i < len;i++)
	{
		char c = url_str[i];

		if (c == '%' && ((i + 2) < len))
		{
			char hex_str[8];
			UINT value;

			hex_str[0] = url_str[i + 1];
			hex_str[1] = url_str[i + 2];
			hex_str[2] = 0;

			value = HexToInt(hex_str);

			WriteBufChar(b, (UCHAR)value);

			i += 2;
			continue;
		}
		else
		{
			if (c == '+')
			{
				c = ' ';
			}
			WriteBufChar(b, c);
		}
	}

	WriteBufChar(b, 0);

	ret = CopyStr(b->Buf);

	FreeBuf(b);

	return ret;
}