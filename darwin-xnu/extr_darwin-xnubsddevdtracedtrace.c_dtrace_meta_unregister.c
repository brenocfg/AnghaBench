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
struct TYPE_4__ {scalar_t__ dtm_count; int /*<<< orphan*/  dtm_name; } ;
typedef  TYPE_1__ dtrace_meta_t ;
typedef  scalar_t__ dtrace_meta_provider_id_t ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  dtrace_lock ; 
 int /*<<< orphan*/  dtrace_meta_lock ; 
 TYPE_1__* dtrace_meta_pid ; 
 int /*<<< orphan*/  dtrace_strunref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,void*) ; 

int
dtrace_meta_unregister(dtrace_meta_provider_id_t id)
{
	dtrace_meta_t **pp, *old = (dtrace_meta_t *)id;

	lck_mtx_lock(&dtrace_meta_lock);
	lck_mtx_lock(&dtrace_lock);

	if (old == dtrace_meta_pid) {
		pp = &dtrace_meta_pid;
	} else {
		panic("attempt to unregister non-existent "
		    "dtrace meta-provider %p\n", (void *)old);
	}

	if (old->dtm_count != 0) {
		lck_mtx_unlock(&dtrace_lock);
		lck_mtx_unlock(&dtrace_meta_lock);
		return (EBUSY);
	}

	*pp = NULL;

	dtrace_strunref(old->dtm_name);

	lck_mtx_unlock(&dtrace_lock);
	lck_mtx_unlock(&dtrace_meta_lock);

	kmem_free(old, sizeof (dtrace_meta_t));

	return (0);
}