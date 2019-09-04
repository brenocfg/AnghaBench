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
struct TYPE_5__ {int lockcount; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  __unlist_locked_file (TYPE_1__*) ; 
 int /*<<< orphan*/  __unlockfile (TYPE_1__*) ; 

void funlockfile(FILE *f)
{
	if (f->lockcount == 1) {
		__unlist_locked_file(f);
		f->lockcount = 0;
		__unlockfile(f);
	} else {
		f->lockcount--;
	}
}