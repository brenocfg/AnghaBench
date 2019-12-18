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
 unsigned int SMD_EVENT_DATA ; 
 scalar_t__ rpcrouter_need_len ; 
 int /*<<< orphan*/  rpcrouter_wake_lock ; 
 int /*<<< orphan*/  smd_channel ; 
 scalar_t__ smd_read_avail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smd_wait ; 
 int /*<<< orphan*/  wake_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rpcrouter_smdnotify(void *_dev, unsigned event)
{
	if (event != SMD_EVENT_DATA)
		return;

	if (smd_read_avail(smd_channel) >= rpcrouter_need_len)
		wake_lock(&rpcrouter_wake_lock);
	wake_up(&smd_wait);
}