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
typedef  scalar_t__ boolean_t ;
struct TYPE_6__ {int returnval; int flags; int /*<<< orphan*/  errorval; } ;
typedef  TYPE_1__ aio_workq_entry ;

/* Variables and functions */
 int AIO_DISABLE ; 
 int /*<<< orphan*/  ECANCELED ; 
 int /*<<< orphan*/  aio_entry_lock_spin (TYPE_1__*) ; 
 int /*<<< orphan*/  aio_entry_ref_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  aio_entry_unlock (TYPE_1__*) ; 

__attribute__((used)) static void		
aio_entry_update_for_cancel(aio_workq_entry *entryp, boolean_t cancelled, int wait_for_completion, boolean_t disable_notification)
{
	aio_entry_lock_spin(entryp);

	if (cancelled) {
		aio_entry_ref_locked(entryp);
		entryp->errorval = ECANCELED;
		entryp->returnval = -1;
	}
	
	if ( wait_for_completion ) {
		entryp->flags |= wait_for_completion; /* flag for special completion processing */
	}
	
	if ( disable_notification ) { 
		entryp->flags |= AIO_DISABLE; /* Don't want a signal */
	}

	aio_entry_unlock(entryp); 
}