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
struct path {int dummy; } ;

/* Variables and functions */
 scalar_t__ kern_path (char const*,int /*<<< orphan*/ ,struct path*) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 char* tomoyo_realpath_from_path (struct path*) ; 

char *tomoyo_realpath_nofollow(const char *pathname)
{
	struct path path;

	if (pathname && kern_path(pathname, 0, &path) == 0) {
		char *buf = tomoyo_realpath_from_path(&path);
		path_put(&path);
		return buf;
	}
	return NULL;
}