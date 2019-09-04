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
 int /*<<< orphan*/  bsd_log_init () ; 
 int /*<<< orphan*/  bsd_log_spinlock ; 
 int /*<<< orphan*/  printf_lock ; 
 int /*<<< orphan*/  simple_lock_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void

printf_init(void)
{
	/*
	 * Lock is only really needed after the first thread is created.
	 */
	simple_lock_init(&printf_lock, 0);
	simple_lock_init(&bsd_log_spinlock, 0);
	bsd_log_init();
}