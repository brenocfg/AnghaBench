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
struct super_block {int /*<<< orphan*/  s_fs_info; } ;
struct pid_namespace {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_pid_ns (struct pid_namespace*) ; 
 int set_anon_super (struct super_block*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int proc_set_super(struct super_block *sb, void *data)
{
	struct pid_namespace *ns;

	ns = (struct pid_namespace *)data;
	sb->s_fs_info = get_pid_ns(ns);
	return set_anon_super(sb, NULL);
}