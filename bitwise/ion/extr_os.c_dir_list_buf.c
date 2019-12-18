#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  name; scalar_t__ valid; } ;
typedef  TYPE_1__ DirListIter ;

/* Variables and functions */
 int /*<<< orphan*/  buf_push (char const**,char const*) ; 
 int /*<<< orphan*/  dir_list (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  dir_list_next (TYPE_1__*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 

const char **dir_list_buf(const char *filespec) {
    const char **buf = NULL;
    DirListIter iter;
    for (dir_list(&iter, filespec); iter.valid; dir_list_next(&iter)) {
        const char *name = strdup(iter.name);
        buf_push(buf, name);
    }
    return buf;
}