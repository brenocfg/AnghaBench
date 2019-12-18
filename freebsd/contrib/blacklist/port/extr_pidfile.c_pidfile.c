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
 int create_pidfile (char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* generate_varrun_path (char const*) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 

int
pidfile(const char *path)
{

	if (path == NULL || strchr(path, '/') == NULL) {
		char *default_path;

		if ((default_path = generate_varrun_path(path)) == NULL)
			return -1;

		if (create_pidfile(default_path) == -1) {
			free(default_path);
			return -1;
		}

		free(default_path);
		return 0;
	} else
		return create_pidfile(path);
}