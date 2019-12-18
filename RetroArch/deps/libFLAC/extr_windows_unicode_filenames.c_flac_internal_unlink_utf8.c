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
 int _unlink (char const*) ; 
 int _wunlink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  utf8_filenames ; 
 int /*<<< orphan*/ * wchar_from_utf8 (char const*) ; 

int flac_internal_unlink_utf8(const char *filename)
{
	if (!utf8_filenames) {
		return _unlink(filename);
	} else {
		wchar_t *wname;
		int ret;

		if (!(wname = wchar_from_utf8(filename))) return -1;
		ret = _wunlink(wname);
		free(wname);

		return ret;
	}
}