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
 int /*<<< orphan*/  bsd_log_spinlock ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 

void
bsd_log_lock(void)
{
	simple_lock(&bsd_log_spinlock);
}