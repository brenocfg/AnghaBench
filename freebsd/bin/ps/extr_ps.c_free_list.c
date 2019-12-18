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
struct listinfo {TYPE_1__ l; int /*<<< orphan*/ * lname; int /*<<< orphan*/ * addelem; scalar_t__ maxcount; scalar_t__ elemsize; scalar_t__ count; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
free_list(struct listinfo *inf)
{

	inf->count = inf->elemsize = inf->maxcount = 0;
	if (inf->l.ptr != NULL)
		free(inf->l.ptr);
	inf->addelem = NULL;
	inf->lname = NULL;
	inf->l.ptr = NULL;
}