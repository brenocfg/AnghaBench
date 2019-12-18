#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct _finddata_t {int dummy; } ;
struct TYPE_6__ {scalar_t__ handle; int /*<<< orphan*/  valid; } ;
typedef  TYPE_1__ DirListIter ;

/* Variables and functions */
 int _findnext (intptr_t,struct _finddata_t*) ; 
 int /*<<< orphan*/  dir__update (TYPE_1__*,int,struct _finddata_t*) ; 
 scalar_t__ dir_excluded (TYPE_1__*) ; 
 int /*<<< orphan*/  dir_list_free (TYPE_1__*) ; 

void dir_list_next(DirListIter *iter) {
    if (!iter->valid) {
        return;
    }
    do {
        struct _finddata_t fileinfo;
        int result = _findnext((intptr_t)iter->handle, &fileinfo);
        dir__update(iter, result != 0, &fileinfo);
        if (result != 0) {
            dir_list_free(iter);
            return;
        }
    } while (dir_excluded(iter));
}