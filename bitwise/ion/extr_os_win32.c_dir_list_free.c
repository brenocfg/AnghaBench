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
struct TYPE_3__ {int valid; int error; scalar_t__ handle; } ;
typedef  TYPE_1__ DirListIter ;

/* Variables and functions */
 int /*<<< orphan*/  _findclose (intptr_t) ; 

void dir_list_free(DirListIter *iter) {
    if (iter->valid) {
        _findclose((intptr_t)iter->handle);
        iter->valid = false;
        iter->error = false;
    }
}