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
 char* extension_table ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max_ext_width ; 
 int nexts ; 
 int /*<<< orphan*/  pkg_extensions_lck ; 
 int strlen (char const*) ; 
 scalar_t__ strncasecmp (char const*,char const*,int) ; 

int is_package_name(const char *name, int len)
{
    int i, extlen;
    const char *ptr, *name_ext;
    
    if (len <= 3) {
	return 0;
    }

    name_ext = NULL;
    for(ptr=name; *ptr != '\0'; ptr++) {
	if (*ptr == '.') {
	    name_ext = ptr;
	}
    }

    // if there is no "." extension, it can't match
    if (name_ext == NULL) {
	return 0;
    }

    // advance over the "."
    name_ext++;

    lck_mtx_lock(pkg_extensions_lck);

    // now iterate over all the extensions to see if any match
    ptr = &extension_table[0];
    for(i=0; i < nexts; i++, ptr+=max_ext_width) {
	extlen = strlen(ptr);
	if (strncasecmp(name_ext, ptr, extlen) == 0 && name_ext[extlen] == '\0') {
	    // aha, a match!
	    lck_mtx_unlock(pkg_extensions_lck);
	    return 1;
	}
    }

    lck_mtx_unlock(pkg_extensions_lck);

    // if we get here, no extension matched
    return 0;
}