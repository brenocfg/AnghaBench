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
typedef  int /*<<< orphan*/  Dwarf_Files ;
typedef  int /*<<< orphan*/  Dwarf_Die ;

/* Variables and functions */
 char* dwarf_filesrc (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dwarf_getsrcfiles (int /*<<< orphan*/ *,int /*<<< orphan*/ **,size_t*) ; 
 scalar_t__ strtailcmp (char const*,char const*) ; 

const char *cu_find_realpath(Dwarf_Die *cu_die, const char *fname)
{
	Dwarf_Files *files;
	size_t nfiles, i;
	const char *src = NULL;
	int ret;

	if (!fname)
		return NULL;

	ret = dwarf_getsrcfiles(cu_die, &files, &nfiles);
	if (ret != 0)
		return NULL;

	for (i = 0; i < nfiles; i++) {
		src = dwarf_filesrc(files, i, NULL, NULL);
		if (strtailcmp(src, fname) == 0)
			break;
	}
	if (i == nfiles)
		return NULL;
	return src;
}