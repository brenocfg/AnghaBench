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
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/ * NewBuf () ; 
 int StartWith (char*,char*) ; 
 int /*<<< orphan*/  StrLen (char*) ; 
 int /*<<< orphan*/ * StrToBin (char*) ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

BUF *IkeStrToPassword(char *str)
{
	BUF *b;
	// Validate arguments
	if (str == NULL)
	{
		return NewBuf();
	}

	if (StartWith(str, "0x") == false)
	{
		// Accept the string as is
		b = NewBuf();
		WriteBuf(b, str, StrLen(str));
	}
	else
	{
		// Interpret as a hexadecimal value
		b = StrToBin(str + 2);
	}

	return b;
}