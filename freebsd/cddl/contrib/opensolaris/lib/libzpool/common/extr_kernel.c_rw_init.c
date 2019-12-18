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
struct TYPE_3__ {scalar_t__ rw_count; int /*<<< orphan*/  initialized; int /*<<< orphan*/ * rw_owner; int /*<<< orphan*/  rw_lock; } ;
typedef  TYPE_1__ krwlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  USYNC_THREAD ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
rw_init(krwlock_t *rwlp, char *name, int type, void *arg)
{
	rwlock_init(&rwlp->rw_lock, USYNC_THREAD, NULL);
	rwlp->rw_owner = NULL;
	rwlp->initialized = B_TRUE;
	rwlp->rw_count = 0;
}