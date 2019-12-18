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
struct super_block {struct pid_namespace* s_fs_info; } ;
struct pid_namespace {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  proc_parse_options (char*,struct pid_namespace*) ; 

int proc_remount(struct super_block *sb, int *flags, char *data)
{
	struct pid_namespace *pid = sb->s_fs_info;
	return !proc_parse_options(data, pid);
}