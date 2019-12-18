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
typedef  int /*<<< orphan*/  utf8 ;
typedef  int UCHAR ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/ * NewBuf () ; 
 int StrLen (int*) ; 
 int /*<<< orphan*/  UniToStr (int*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,int*,int) ; 

BUF *RadiusCreateUserName(wchar_t *username)
{
	BUF *b;
	UCHAR code, size;
	UCHAR utf8[254];
	// Validate arguments
	if (username == NULL)
	{
		return NULL;
	}

	// Convert the user name to a Unicode string
	UniToStr(utf8, sizeof(utf8), username);
	utf8[253] = 0;

	b = NewBuf();
	code = 1;
	size = 2 + (UCHAR)StrLen(utf8);
	WriteBuf(b, &code, 1);
	WriteBuf(b, &size, 1);
	WriteBuf(b, utf8, StrLen(utf8));

	return b;
}