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
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int IsEmptyStr (char*) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  MakeSafeLogStr (char*) ; 
 int /*<<< orphan*/  StrCat (char*,int,char*) ; 
 size_t StrLen (char*) ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,char*,size_t) ; 

void AddLogBufToStr(BUF *b, char *name, char *value)
{
	char tmp[MAX_SIZE * 2];
	char *p = NULL;
	// Validate arguments
	if (b == NULL || value == NULL)
	{
		return;
	}

	if (IsEmptyStr(value))
	{
		return;
	}

	tmp[0] = 0;

	if (IsEmptyStr(name) == false)
	{
		p = &tmp[StrLen(tmp)];
		StrCat(tmp, sizeof(tmp), name);
		MakeSafeLogStr(p);
		StrCat(tmp, sizeof(tmp), "=");
	}

	p = &tmp[StrLen(tmp)];
	StrCat(tmp, sizeof(tmp), value);
	MakeSafeLogStr(p);
	StrCat(tmp, sizeof(tmp), " ");

	WriteBuf(b, tmp, StrLen(tmp));
}