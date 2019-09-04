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
typedef  char UCHAR ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/ * NewBuf () ; 
 int StrLen (char*) ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,char*,int) ; 

BUF *RadiusCreateNasId(char *name)
{
	BUF *b;
	UCHAR code, size;
	// Validate arguments
	if (name == NULL)
	{
		return NULL;
	}
	if (StrLen(name) == 0 || StrLen(name) >= 128)
	{
		return NULL;
	}

	b = NewBuf();
	code = 32;
	size = 2 + (UCHAR)StrLen(name);
	WriteBuf(b, &code, 1);
	WriteBuf(b, &size, 1);
	WriteBuf(b, name, StrLen(name));

	return b;
}