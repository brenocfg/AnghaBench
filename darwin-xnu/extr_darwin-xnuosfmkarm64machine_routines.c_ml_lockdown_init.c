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

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lck_grp_alloc_init (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lockdown_handler_grp ; 
 int /*<<< orphan*/  lockdown_handler_lck ; 

void ml_lockdown_init() {
    lockdown_handler_grp = lck_grp_alloc_init("lockdown_handler", NULL);
    assert(lockdown_handler_grp != NULL);

    lck_mtx_init(&lockdown_handler_lck, lockdown_handler_grp, NULL);

}