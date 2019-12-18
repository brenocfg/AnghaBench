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
struct hpsb_host {int /*<<< orphan*/  id; } ;
struct host_info {int /*<<< orphan*/  thread; struct hpsb_host* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPSB_ERR (char*,...) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 struct host_info* hpsb_create_hostinfo (int /*<<< orphan*/ *,struct hpsb_host*,int) ; 
 int /*<<< orphan*/  hpsb_destroy_hostinfo (int /*<<< orphan*/ *,struct hpsb_host*) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,struct hpsb_host*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nodemgr_highlevel ; 
 int /*<<< orphan*/  nodemgr_host_thread ; 

__attribute__((used)) static void nodemgr_add_host(struct hpsb_host *host)
{
	struct host_info *hi;

	hi = hpsb_create_hostinfo(&nodemgr_highlevel, host, sizeof(*hi));
	if (!hi) {
		HPSB_ERR("NodeMgr: out of memory in add host");
		return;
	}
	hi->host = host;
	hi->thread = kthread_run(nodemgr_host_thread, host, "knodemgrd_%d",
				 host->id);
	if (IS_ERR(hi->thread)) {
		HPSB_ERR("NodeMgr: cannot start thread for host %d", host->id);
		hpsb_destroy_hostinfo(&nodemgr_highlevel, host);
	}
}