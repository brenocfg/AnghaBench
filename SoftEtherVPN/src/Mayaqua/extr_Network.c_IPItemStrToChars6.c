#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_4__ {scalar_t__ Buf; } ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  FreeBuf (TYPE_1__*) ; 
 int StrLen (char*) ; 
 TYPE_1__* StrToBin (char*) ; 
 int /*<<< orphan*/  Zero (char*,int) ; 

void IPItemStrToChars6(UCHAR *chars, char *str)
{
	char tmp[5];
	BUF *b;
	UINT len;
	// Validate arguments
	if (chars == NULL)
	{
		return;
	}

	Zero(tmp, sizeof(tmp));

	len = StrLen(str);
	switch (len)
	{
	case 0:
		tmp[0] = tmp[1] = tmp[2] = tmp[3] = '0';
		break;

	case 1:
		tmp[0] = tmp[1] = tmp[2] = '0';
		tmp[3] = str[0];
		break;

	case 2:
		tmp[0] = tmp[1] = '0';
		tmp[2] = str[0];
		tmp[3] = str[1];
		break;

	case 3:
		tmp[0] = '0';
		tmp[1] = str[0];
		tmp[2] = str[1];
		tmp[3] = str[2];
		break;

	case 4:
		tmp[0] = str[0];
		tmp[1] = str[1];
		tmp[2] = str[2];
		tmp[3] = str[3];
		break;
	}

	b = StrToBin(tmp);

	chars[0] = ((UCHAR *)b->Buf)[0];
	chars[1] = ((UCHAR *)b->Buf)[1];

	FreeBuf(b);
}