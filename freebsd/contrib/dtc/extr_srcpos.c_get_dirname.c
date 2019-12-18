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
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* strrchr (char const*,char) ; 
 char* xmalloc (int) ; 

__attribute__((used)) static char *get_dirname(const char *path)
{
	const char *slash = strrchr(path, '/');

	if (slash) {
		int len = slash - path;
		char *dir = xmalloc(len + 1);

		memcpy(dir, path, len);
		dir[len] = '\0';
		return dir;
	}
	return NULL;
}