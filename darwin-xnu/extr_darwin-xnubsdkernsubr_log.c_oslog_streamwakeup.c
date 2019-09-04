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
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  lck_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ oslog_is_safe () ; 
 int /*<<< orphan*/  oslog_stream_lock ; 
 int /*<<< orphan*/  oslog_streamwakeup_locked () ; 

void
oslog_streamwakeup(void)
{
	/* cf. r24974766 & r25201228*/
	if (oslog_is_safe() == FALSE) {
		return;
	}

	lck_spin_lock(&oslog_stream_lock);
	oslog_streamwakeup_locked();
	lck_spin_unlock(&oslog_stream_lock);
}