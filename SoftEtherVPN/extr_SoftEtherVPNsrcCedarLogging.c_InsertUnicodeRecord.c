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
typedef  int /*<<< orphan*/  LOG ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ CalcUniToUtf8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  InsertStringRecord (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  UniToUtf8 (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 char* ZeroMalloc (scalar_t__) ; 

void InsertUnicodeRecord(LOG *g, wchar_t *unistr)
{
	char *str;
	UINT size;
	// Validate arguments
	if (g == NULL || unistr == NULL)
	{
		return;
	}

	size = CalcUniToUtf8(unistr) + 32;
	str = ZeroMalloc(size);

	UniToUtf8((BYTE *)str, size, unistr);
	InsertStringRecord(g, str);
	Free(str);
}