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
struct rc_pid_sta_info {int /*<<< orphan*/  events_entry; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_IRUGO ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int /*<<< orphan*/ ,struct dentry*,struct rc_pid_sta_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rc_pid_fop_events ; 

void rate_control_pid_add_sta_debugfs(void *priv, void *priv_sta,
					     struct dentry *dir)
{
	struct rc_pid_sta_info *spinfo = priv_sta;

	spinfo->events_entry = debugfs_create_file("rc_pid_events", S_IRUGO,
						   dir, spinfo,
						   &rc_pid_fop_events);
}