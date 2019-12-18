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

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 scalar_t__ MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 

__attribute__((used)) static wchar_t *wchar_from_utf8(const char *str)
{
	wchar_t *widestr;
	int len;

	if (!str)
		return NULL;
	if ((len = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0)) == 0)
		return NULL;
	if ((widestr = (wchar_t *)malloc(len*sizeof(wchar_t))) == NULL)
		return NULL;
	if (MultiByteToWideChar(CP_UTF8, 0, str, -1, widestr, len) == 0) {
		free(widestr);
		widestr = NULL;
	}

	return widestr;
}