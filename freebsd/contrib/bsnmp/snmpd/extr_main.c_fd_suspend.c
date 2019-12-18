#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct fdesc {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  evDeselectFD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  evInitID (int*) ; 
 scalar_t__ evTestID (int) ; 
 int /*<<< orphan*/  evctx ; 
 int /*<<< orphan*/  poll_unregister (int) ; 

void
fd_suspend(void *p)
{
	struct fdesc *f = p;

#ifdef USE_LIBBEGEMOT
	if (f->id >= 0) {
		poll_unregister(f->id);
		f->id = -1;
	}
#else
	if (evTestID(f->id)) {
		(void)evDeselectFD(evctx, f->id);
		evInitID(&f->id);
	}
#endif
}