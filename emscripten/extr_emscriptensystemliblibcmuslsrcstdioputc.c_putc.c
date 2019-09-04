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
struct TYPE_6__ {scalar_t__ lock; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  __lockfile (TYPE_1__*) ; 
 int /*<<< orphan*/  __unlockfile (TYPE_1__*) ; 
 int putc_unlocked (int,TYPE_1__*) ; 

int putc(int c, FILE *f)
{
	if (f->lock < 0 || !__lockfile(f))
		return putc_unlocked(c, f);
	c = putc_unlocked(c, f);
	__unlockfile(f);
	return c;
}