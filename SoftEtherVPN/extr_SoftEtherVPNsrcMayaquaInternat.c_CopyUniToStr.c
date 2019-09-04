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
typedef  scalar_t__ UINT ;

/* Variables and functions */
 scalar_t__ CalcUniToStr (int /*<<< orphan*/ *) ; 
 char* CopyStr (char*) ; 
 char* Malloc (scalar_t__) ; 
 int /*<<< orphan*/  UniToStr (char*,scalar_t__,int /*<<< orphan*/ *) ; 

char *CopyUniToStr(wchar_t *unistr)
{
	char *str;
	UINT str_size;
	// Validate arguments
	if (unistr == NULL)
	{
		return NULL;
	}

	str_size = CalcUniToStr(unistr);
	if (str_size == 0)
	{
		return CopyStr("");
	}
	str = Malloc(str_size);
	UniToStr(str, str_size, unistr);

	return str;
}