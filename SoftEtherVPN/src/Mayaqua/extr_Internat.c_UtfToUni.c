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
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */
 char* CopyUtfToUni (char*) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  UniStrCpy (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  UniStrLen (char*) ; 

UINT UtfToUni(wchar_t *unistr, UINT size, char *utfstr)
{
	wchar_t *tmp;
	// Validate arguments
	if (unistr == NULL || utfstr == NULL)
	{
		UniStrCpy(unistr, size, L"");
		return 0;
	}

	tmp = CopyUtfToUni(utfstr);

	UniStrCpy(unistr, size, tmp);

	Free(tmp);

	return UniStrLen(unistr);
}