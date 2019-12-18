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
 int /*<<< orphan*/  die (char*,char const*,char const*) ; 
 int /*<<< orphan*/  streq (char const*,char*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strneq (char const*,char const*,int) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static char *nodename_from_path(const char *ppath, const char *cpath)
{
	int plen;

	plen = strlen(ppath);

	if (!strneq(ppath, cpath, plen))
		die("Path \"%s\" is not valid as a child of \"%s\"\n",
		    cpath, ppath);

	/* root node is a special case */
	if (!streq(ppath, "/"))
		plen++;

	return xstrdup(cpath + plen);
}