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
struct seq_file {struct cgroup_pidlist* private; } ;
struct cgroup_pidlist {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cgroup_pidlist_stop(struct seq_file *s, void *v)
{
	struct cgroup_pidlist *l = s->private;
	up_read(&l->mutex);
}