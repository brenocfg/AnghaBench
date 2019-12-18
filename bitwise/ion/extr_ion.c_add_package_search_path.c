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
 scalar_t__ flag_verbose ; 
 int /*<<< orphan*/  num_package_search_paths ; 
 int /*<<< orphan*/ * package_search_paths ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  str_intern (char const*) ; 

void add_package_search_path(const char *path) {
    if (flag_verbose) {
        printf("Adding package search path %s\n", path);
    }
    package_search_paths[num_package_search_paths++] = str_intern(path);
}