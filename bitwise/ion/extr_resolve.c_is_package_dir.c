#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char const* name; scalar_t__ valid; } ;
typedef  TYPE_1__ DirListIter ;

/* Variables and functions */
 int MAX_PATH ; 
 int /*<<< orphan*/  dir_list (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dir_list_free (TYPE_1__*) ; 
 int /*<<< orphan*/  dir_list_next (TYPE_1__*) ; 
 int /*<<< orphan*/  path_copy (char*,char const*) ; 
 char* path_ext (char const*) ; 
 int /*<<< orphan*/  path_join (char*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

bool is_package_dir(const char *search_path, const char *package_path) {
    char path[MAX_PATH];
    path_copy(path, search_path);
    path_join(path, package_path);
    DirListIter iter;
    for (dir_list(&iter, path); iter.valid; dir_list_next(&iter)) {
        const char *ext = path_ext(iter.name);
        if (ext != iter.name && strcmp(ext, "ion") == 0) {
            dir_list_free(&iter);
            return true;
        }
    }
    return false;
}