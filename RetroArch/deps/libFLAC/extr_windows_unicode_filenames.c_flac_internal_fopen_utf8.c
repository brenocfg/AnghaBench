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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * _wfopen (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char const*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  utf8_filenames ; 
 int /*<<< orphan*/ * wchar_from_utf8 (char const*) ; 

FILE* flac_internal_fopen_utf8(const char *filename, const char *mode)
{
	if (!utf8_filenames) {
		return fopen(filename, mode);
	} else {
		wchar_t *wname = NULL;
		wchar_t *wmode = NULL;
		FILE *f = NULL;

		do {
			if (!(wname = wchar_from_utf8(filename))) break;
			if (!(wmode = wchar_from_utf8(mode))) break;
			f = _wfopen(wname, wmode);
		} while(0);

		free(wname);
		free(wmode);

		return f;
	}
}