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
struct TYPE_5__ {int /*<<< orphan*/  base; int /*<<< orphan*/  name; int /*<<< orphan*/  is_dir; int /*<<< orphan*/  valid; } ;
typedef  TYPE_1__ DirListIter ;

/* Variables and functions */
 int /*<<< orphan*/  dir_list (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dir_list_free (TYPE_1__*) ; 
 int /*<<< orphan*/  path_join (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool dir_list_subdir(DirListIter *iter) {
    if (!iter->valid || !iter->is_dir) {
        return false;
    }
    DirListIter subdir_iter;
    path_join(iter->base, iter->name);
    dir_list(&subdir_iter, iter->base);
    dir_list_free(iter);
    *iter = subdir_iter;
    return true;
}