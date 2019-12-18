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

/* Variables and functions */
 scalar_t__ strip_rcs_crap (char*) ; 
 int /*<<< orphan*/  write_version (char const*,char*,unsigned long) ; 

void maybe_frob_rcs_version(const char *modfilename,
			    char *version,
			    void *modinfo,
			    unsigned long version_offset)
{
	if (strip_rcs_crap(version))
		write_version(modfilename, version, version_offset);
}