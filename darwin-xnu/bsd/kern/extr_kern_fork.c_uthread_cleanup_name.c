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
typedef  TYPE_1__* uthread_t ;
struct TYPE_2__ {int /*<<< orphan*/ * pth_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAXTHREADNAMESIZE ; 
 int /*<<< orphan*/  kfree (void*,int /*<<< orphan*/ ) ; 

void
uthread_cleanup_name(void *uthread)
{
	uthread_t uth = (uthread_t)uthread;

	/*
	 * <rdar://17834538>
	 * Set pth_name to NULL before calling free().
	 * Previously there was a race condition in the
	 * case this code was executing during a stackshot
	 * where the stackshot could try and copy pth_name
	 * after it had been freed and before if was marked
	 * as null.
	 */
	if (uth->pth_name != NULL) {
		void *pth_name = uth->pth_name;
		uth->pth_name = NULL;
		kfree(pth_name, MAXTHREADNAMESIZE);
	}
	return;
}