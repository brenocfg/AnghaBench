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
struct dirent {int d_type; int /*<<< orphan*/  d_name; } ;
struct TYPE_5__ {int is_dir; int /*<<< orphan*/  name; int /*<<< orphan*/  handle; int /*<<< orphan*/  valid; } ;
typedef  TYPE_1__ DirListIter ;

/* Variables and functions */
 int DT_DIR ; 
 scalar_t__ dir_excluded (TYPE_1__*) ; 
 int /*<<< orphan*/  dir_list_free (TYPE_1__*) ; 
 int /*<<< orphan*/  path_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dirent* readdir (int /*<<< orphan*/ ) ; 

void dir_list_next(DirListIter *iter) {
    if (!iter->valid) {
        return;
    }
    do {
        struct dirent *entry = readdir(iter->handle);
        if (!entry) {
            dir_list_free(iter);
            return;
        }
        path_copy(iter->name, entry->d_name);
        iter->is_dir = entry->d_type & DT_DIR;
    } while (dir_excluded(iter));
}