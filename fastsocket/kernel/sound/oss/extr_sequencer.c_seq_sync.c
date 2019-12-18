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
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  interruptible_sleep_on_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ qlen ; 
 int /*<<< orphan*/  seq_playing ; 
 int /*<<< orphan*/  seq_sleeper ; 
 int /*<<< orphan*/  seq_startplay () ; 
 int /*<<< orphan*/  signal_pending (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int seq_sync(void)
{
	if (qlen && !seq_playing && !signal_pending(current))
		seq_startplay();

 	if (qlen > 0)
 		interruptible_sleep_on_timeout(&seq_sleeper, HZ);
	return qlen;
}