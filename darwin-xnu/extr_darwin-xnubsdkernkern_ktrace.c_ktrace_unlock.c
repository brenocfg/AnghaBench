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
 int /*<<< orphan*/  ktrace_mtx ; 
 int /*<<< orphan*/  ktrace_single_threaded ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 

void
ktrace_unlock(void)
{
	if (!ktrace_single_threaded) {
		lck_mtx_unlock(ktrace_mtx);
	}
}