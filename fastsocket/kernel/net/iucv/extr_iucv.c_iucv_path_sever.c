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
typedef  int /*<<< orphan*/  u8 ;
struct iucv_path {size_t pathid; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ cpus_empty (int /*<<< orphan*/ ) ; 
 scalar_t__ iucv_active_cpu ; 
 int /*<<< orphan*/  iucv_buffer_cpumask ; 
 int /*<<< orphan*/ ** iucv_path_table ; 
 int iucv_sever_pathid (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iucv_table_lock ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 scalar_t__ smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int iucv_path_sever(struct iucv_path *path, u8 userdata[16])
{
	int rc;

	preempt_disable();
	if (cpus_empty(iucv_buffer_cpumask)) {
		rc = -EIO;
		goto out;
	}
	if (iucv_active_cpu != smp_processor_id())
		spin_lock_bh(&iucv_table_lock);
	rc = iucv_sever_pathid(path->pathid, userdata);
	iucv_path_table[path->pathid] = NULL;
	list_del_init(&path->list);
	if (iucv_active_cpu != smp_processor_id())
		spin_unlock_bh(&iucv_table_lock);
out:
	preempt_enable();
	return rc;
}