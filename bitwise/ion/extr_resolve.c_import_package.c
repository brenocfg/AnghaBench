#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char const* path; int /*<<< orphan*/  full_path; } ;
typedef  TYPE_1__ Package ;

/* Variables and functions */
 int MAX_PATH ; 
 int /*<<< orphan*/  add_package (TYPE_1__*) ; 
 int /*<<< orphan*/  compile_package (TYPE_1__*) ; 
 int /*<<< orphan*/  copy_package_full_path (char*,char const*) ; 
 scalar_t__ flag_verbose ; 
 TYPE_1__* map_get (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  package_map ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 char* str_intern (char const*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* xcalloc (int,int) ; 

Package *import_package(const char *package_path) {
    package_path = str_intern(package_path);
    Package *package = map_get(&package_map, package_path);
    if (!package) {
        package = xcalloc(1, sizeof(Package));
        package->path = package_path;
        if (flag_verbose) {
            printf("Importing %s\n", package_path);
        }
        char full_path[MAX_PATH];
        if (!copy_package_full_path(full_path, package_path)) {
            return NULL;
        }
        strcpy(package->full_path, full_path);
        add_package(package);
        compile_package(package);
    }
    return package;
}