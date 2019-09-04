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
typedef  int UINT ;

/* Variables and functions */
 int /*<<< orphan*/  AnsiGetLineUnix (char*,int) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int,char*) ; 
 char* ZeroMalloc (int) ; 

bool UniGetLineUnix(wchar_t *str, UINT size)
{
	char *str_a;
	UINT str_a_size = size;
	if (str == NULL || size < sizeof(wchar_t))
	{
		return false;
	}
	if (str_a_size >= 0x7fffffff)
	{
		str_a_size = MAX_SIZE;
	}
	str_a_size *= 2;

	str_a = ZeroMalloc(str_a_size);

	AnsiGetLineUnix(str_a, str_a_size);

	StrToUni(str, size, str_a);

	Free(str_a);

	return true;
}