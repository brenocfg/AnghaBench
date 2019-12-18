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
 int _wrename (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int rename (char const*,char const*) ; 
 int /*<<< orphan*/  utf8_filenames ; 
 int /*<<< orphan*/ * wchar_from_utf8 (char const*) ; 

int flac_internal_rename_utf8(const char *oldname, const char *newname)
{
	if (!utf8_filenames) {
		return rename(oldname, newname);
	} else {
		wchar_t *wold = NULL;
		wchar_t *wnew = NULL;
		int ret = -1;

		do {
			if (!(wold = wchar_from_utf8(oldname))) break;
			if (!(wnew = wchar_from_utf8(newname))) break;
			ret = _wrename(wold, wnew);
		} while(0);

		free(wold);
		free(wnew);

		return ret;
	}
}