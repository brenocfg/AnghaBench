#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * ptr; } ;
struct listinfo {int elemsize; char const* lname; TYPE_1__ l; int /*<<< orphan*/  addelem; scalar_t__ maxcount; scalar_t__ count; } ;
typedef  int /*<<< orphan*/  addelem_rtn ;

/* Variables and functions */

__attribute__((used)) static void
init_list(struct listinfo *inf, addelem_rtn artn, int elemsize,
    const char *lname)
{

	inf->count = inf->maxcount = 0;
	inf->elemsize = elemsize;
	inf->addelem = artn;
	inf->lname = lname;
	inf->l.ptr = NULL;
}