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
struct utimbuf {int /*<<< orphan*/  modtime; int /*<<< orphan*/  actime; } ;
struct __utimbuf64 {int /*<<< orphan*/  modtime; int /*<<< orphan*/  actime; } ;

/* Variables and functions */
 int _wutime64 (int /*<<< orphan*/ *,struct __utimbuf64*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  utf8_filenames ; 
 int utime (char const*,struct utimbuf*) ; 
 int /*<<< orphan*/ * wchar_from_utf8 (char const*) ; 

int flac_internal_utime_utf8(const char *filename, struct utimbuf *times)
{
	if (!utf8_filenames) {
		return utime(filename, times);
	} else {
		wchar_t *wname;
		struct __utimbuf64 ut;
		int ret;

		if (!(wname = wchar_from_utf8(filename))) return -1;
		ut.actime = times->actime;
		ut.modtime = times->modtime;
		ret = _wutime64(wname, &ut);
		free(wname);

		return ret;
	}
}