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
struct _finddata_t {int dummy; } ;
struct TYPE_7__ {char* base; void* handle; } ;
typedef  TYPE_1__ DirListIter ;

/* Variables and functions */
 int MAX_PATH ; 
 intptr_t _findfirst (char*,struct _finddata_t*) ; 
 int /*<<< orphan*/  dir__update (TYPE_1__*,int,struct _finddata_t*) ; 
 scalar_t__ dir_excluded (TYPE_1__*) ; 
 int /*<<< orphan*/  dir_list_next (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  path_copy (char*,char const*) ; 
 int /*<<< orphan*/  path_join (char*,char*) ; 

void dir_list(DirListIter *iter, const char *path) {
    memset(iter, 0, sizeof(*iter));
    path_copy(iter->base, path);
    char filespec[MAX_PATH];
    path_copy(filespec, path);
    path_join(filespec, "*");
    struct _finddata_t fileinfo;
    intptr_t handle = _findfirst(filespec, &fileinfo);
    iter->handle = (void *)handle;
    dir__update(iter, handle == -1, &fileinfo);
    if (dir_excluded(iter)) {
        dir_list_next(iter);
    }
}