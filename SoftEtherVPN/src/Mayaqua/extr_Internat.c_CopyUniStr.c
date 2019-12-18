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
 int /*<<< orphan*/ * Malloc (int) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int UniStrLen (int /*<<< orphan*/ *) ; 

wchar_t *CopyUniStr(wchar_t *str)
{
	UINT len;
	wchar_t *dst;
	// Validate arguments
	if (str == NULL)
	{
		return NULL;
	}

	len = UniStrLen(str);
	dst = Malloc((len + 1) * sizeof(wchar_t));
	UniStrCpy(dst, 0, str);

	return dst;
}