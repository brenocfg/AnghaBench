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
struct __stat64 {int dummy; } ;

/* Variables and functions */
 int _stat64 (char const*,struct __stat64*) ; 
 int _wstat64 (int /*<<< orphan*/ *,struct __stat64*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  utf8_filenames ; 
 int /*<<< orphan*/ * wchar_from_utf8 (char const*) ; 

int flac_internal_stat64_utf8(const char *path, struct __stat64 *buffer)
{
	if (!utf8_filenames) {
		return _stat64(path, buffer);
	} else {
		wchar_t *wpath;
		int ret;

		if (!(wpath = wchar_from_utf8(path))) return -1;
		ret = _wstat64(wpath, buffer);
		free(wpath);

		return ret;
	}
}