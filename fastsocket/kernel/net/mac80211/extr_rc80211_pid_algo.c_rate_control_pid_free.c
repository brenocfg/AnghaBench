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
struct rc_pid_debugfs_entries {int /*<<< orphan*/  target; int /*<<< orphan*/  sampling_period; int /*<<< orphan*/  coeff_p; int /*<<< orphan*/  coeff_i; int /*<<< orphan*/  coeff_d; int /*<<< orphan*/  smoothing_shift; int /*<<< orphan*/  sharpen_factor; int /*<<< orphan*/  sharpen_duration; int /*<<< orphan*/  norm_offset; } ;
struct rc_pid_info {struct rc_pid_info* rinfo; struct rc_pid_debugfs_entries dentries; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rc_pid_info*) ; 

__attribute__((used)) static void rate_control_pid_free(void *priv)
{
	struct rc_pid_info *pinfo = priv;
#ifdef CONFIG_MAC80211_DEBUGFS
	struct rc_pid_debugfs_entries *de = &pinfo->dentries;

	debugfs_remove(de->norm_offset);
	debugfs_remove(de->sharpen_duration);
	debugfs_remove(de->sharpen_factor);
	debugfs_remove(de->smoothing_shift);
	debugfs_remove(de->coeff_d);
	debugfs_remove(de->coeff_i);
	debugfs_remove(de->coeff_p);
	debugfs_remove(de->sampling_period);
	debugfs_remove(de->target);
#endif

	kfree(pinfo->rinfo);
	kfree(pinfo);
}