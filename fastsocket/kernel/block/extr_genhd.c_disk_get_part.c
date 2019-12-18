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
struct hd_struct {int dummy; } ;
struct gendisk {int /*<<< orphan*/  part_tbl; } ;
struct disk_part_tbl {int len; int /*<<< orphan*/ * part; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  part_to_dev (struct hd_struct*) ; 
 void* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ unlikely (int) ; 

struct hd_struct *disk_get_part(struct gendisk *disk, int partno)
{
	struct hd_struct *part = NULL;
	struct disk_part_tbl *ptbl;

	if (unlikely(partno < 0))
		return NULL;

	rcu_read_lock();

	ptbl = rcu_dereference(disk->part_tbl);
	if (likely(partno < ptbl->len)) {
		part = rcu_dereference(ptbl->part[partno]);
		if (part)
			get_device(part_to_dev(part));
	}

	rcu_read_unlock();

	return part;
}