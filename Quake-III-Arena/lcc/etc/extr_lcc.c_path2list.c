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
typedef  int /*<<< orphan*/ * List ;

/* Variables and functions */
 int /*<<< orphan*/ * append (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  find (char*,int /*<<< orphan*/ *) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 int /*<<< orphan*/  strsave (char*) ; 

__attribute__((used)) static List path2list(const char *path) {
	List list = NULL;
	char sep = ':';

	if (path == NULL)
		return NULL;
	if (strchr(path, ';'))
		sep = ';';
	while (*path) {
		char *p, buf[512];
		if (p = strchr(path, sep)) {
			assert(p - path < sizeof buf);
			strncpy(buf, path, p - path);
			buf[p-path] = '\0';
		} else {
			assert(strlen(path) < sizeof buf);
			strcpy(buf, path);
		}
		if (!find(buf, list))
			list = append(strsave(buf), list);
		if (p == 0)
			break;
		path = p + 1;
	}
	return list;
}