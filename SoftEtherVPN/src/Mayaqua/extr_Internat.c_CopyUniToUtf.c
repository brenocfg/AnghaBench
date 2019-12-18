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
 scalar_t__ CalcUniToUtf8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniToUtf8 (char*,scalar_t__,int /*<<< orphan*/ *) ; 
 char* ZeroMalloc (scalar_t__) ; 

char *CopyUniToUtf(wchar_t *unistr)
{
	UINT size;
	char *ret;
	// Validate arguments
	if (unistr == NULL)
	{
		return NULL;
	}

	size = CalcUniToUtf8(unistr);
	ret = ZeroMalloc(size + sizeof(char));

	UniToUtf8((char *)ret, size, unistr);

	return ret;
}