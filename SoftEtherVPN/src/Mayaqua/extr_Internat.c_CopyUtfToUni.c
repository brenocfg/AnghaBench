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
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ CalcUtf8ToUni (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ StrLen (char*) ; 
 int /*<<< orphan*/  Utf8ToUni (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * ZeroMalloc (scalar_t__) ; 

wchar_t *CopyUtfToUni(char *utfstr)
{
	UINT size;
	wchar_t *ret;
	UINT utfstr_len;
	// Validate arguments
	if (utfstr == NULL)
	{
		return NULL;
	}

	utfstr_len = StrLen(utfstr);

	size = CalcUtf8ToUni((BYTE *)utfstr, utfstr_len);
	ret = ZeroMalloc(size + sizeof(wchar_t));
	Utf8ToUni(ret, size, (BYTE *)utfstr, utfstr_len);

	return ret;
}