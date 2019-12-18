#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct _finddata_t {int attrib; int /*<<< orphan*/  name; int /*<<< orphan*/  size; } ;
struct TYPE_3__ {int valid; int error; int is_dir; scalar_t__* name; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ DirListIter ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int MAX_PATH ; 
 int _A_SUBDIR ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 

void dir__update(DirListIter *iter, bool done, struct _finddata_t *fileinfo) {
    iter->valid = !done;
    iter->error = done && errno != ENOENT;
    if (!done) {
        iter->size = fileinfo->size;
        memcpy(iter->name, fileinfo->name, sizeof(iter->name) - 1);
        iter->name[MAX_PATH - 1] = 0;
        iter->is_dir = fileinfo->attrib & _A_SUBDIR;
    }
}