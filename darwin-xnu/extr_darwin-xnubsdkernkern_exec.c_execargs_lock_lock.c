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
 int /*<<< orphan*/  execargs_cache_lock ; 
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
execargs_lock_lock(void) {
	lck_mtx_lock_spin(execargs_cache_lock);
}