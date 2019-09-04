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
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (char*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  SearchStrEx (char*,char*,int /*<<< orphan*/ ,int) ; 
 char* ZeroMalloc (int /*<<< orphan*/ ) ; 

UINT SearchAsciiInBinary(void *data, UINT size, char *str, bool case_sensitive)
{
	UINT ret = INFINITE;
	char *tmp;
	// Validate arguments
	if (data == NULL || size == 0 || str == NULL)
	{
		return INFINITE;
	}

	tmp = ZeroMalloc(size + 1);
	Copy(tmp, data, size);

	ret = SearchStrEx(tmp, str, 0, case_sensitive);

	Free(tmp);

	return ret;
}