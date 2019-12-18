#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct svc_stat {TYPE_1__* program; } ;
struct proc_dir_entry {int dummy; } ;
struct file_operations {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pg_name; } ;

/* Variables and functions */
 struct proc_dir_entry* do_register (int /*<<< orphan*/ ,struct svc_stat*,struct file_operations const*) ; 

struct proc_dir_entry *
svc_proc_register(struct svc_stat *statp, const struct file_operations *fops)
{
	return do_register(statp->program->pg_name, statp, fops);
}