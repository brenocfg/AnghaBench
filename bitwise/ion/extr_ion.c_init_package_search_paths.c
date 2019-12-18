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
 int MAX_PATH ; 
 int /*<<< orphan*/  add_package_search_path (char const*) ; 
 int /*<<< orphan*/  add_package_search_path_range (char const*,char const*) ; 
 int /*<<< orphan*/  exit (int) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  path_copy (char*,char const*) ; 
 int /*<<< orphan*/  path_join (char*,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 

void init_package_search_paths(void) {
    const char *ionhome_var = getenv("IONHOME");
    if (!ionhome_var) {
        printf("error: Set the environment variable IONHOME to the Ion home directory (where system_packages is located)\n");
        exit(1);
    }
    char path[MAX_PATH];
    path_copy(path, ionhome_var);
    path_join(path, "system_packages");
    add_package_search_path(path);
    add_package_search_path(".");
    const char *ionpath_var = getenv("IONPATH");
    if (ionpath_var) {
        const char *start = ionpath_var;
        for (const char *ptr = ionpath_var; *ptr; ptr++) {
            if (*ptr == ';') {
                add_package_search_path_range(start, ptr);
                start = ptr + 1;
            }
        }
        if (*start) {
            add_package_search_path(start);
        }
    }
}