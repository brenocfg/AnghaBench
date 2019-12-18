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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int lockdown_done ; 
 int /*<<< orphan*/  lockdown_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdown_handler_lck ; 
 int /*<<< orphan*/  lockdown_this ; 

void ml_lockdown_run_handler() {
    lck_mtx_lock(&lockdown_handler_lck);
    assert(!lockdown_done);

    lockdown_done = 1;
    if (lockdown_handler) {
        lockdown_handler(lockdown_this);
    }
    lck_mtx_unlock(&lockdown_handler_lck);
}