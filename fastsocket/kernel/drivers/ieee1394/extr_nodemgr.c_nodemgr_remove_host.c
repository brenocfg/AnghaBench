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
struct hpsb_host {int /*<<< orphan*/  device; } ;
struct host_info {int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 struct host_info* hpsb_get_hostinfo (int /*<<< orphan*/ *,struct hpsb_host*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nodemgr_highlevel ; 
 int /*<<< orphan*/  nodemgr_remove_host_dev (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nodemgr_remove_host(struct hpsb_host *host)
{
	struct host_info *hi = hpsb_get_hostinfo(&nodemgr_highlevel, host);

	if (hi) {
		kthread_stop(hi->thread);
		nodemgr_remove_host_dev(&host->device);
	}
}