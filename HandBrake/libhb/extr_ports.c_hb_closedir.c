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
struct TYPE_5__ {int /*<<< orphan*/  wdir; } ;
typedef  TYPE_1__ HB_DIR ;

/* Variables and functions */
 int _wclosedir (int /*<<< orphan*/ ) ; 
 int closedir (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

int hb_closedir(HB_DIR *dir)
{
#ifdef SYS_MINGW
    int ret;

    ret = _wclosedir(dir->wdir);
    free(dir);
    return ret;
#else
    return closedir(dir);
#endif
}