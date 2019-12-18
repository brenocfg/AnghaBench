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
struct the_nilfs {int /*<<< orphan*/ * ns_sbh; int /*<<< orphan*/  ns_gc_dat; int /*<<< orphan*/  ns_dat; int /*<<< orphan*/  ns_cpfile; int /*<<< orphan*/  ns_sufile; int /*<<< orphan*/  ns_list; int /*<<< orphan*/  ns_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct the_nilfs*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  nilfs_destroy_gccache (struct the_nilfs*) ; 
 scalar_t__ nilfs_init (struct the_nilfs*) ; 
 scalar_t__ nilfs_loaded (struct the_nilfs*) ; 
 int /*<<< orphan*/  nilfs_lock ; 
 int /*<<< orphan*/  nilfs_mdt_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_mdt_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void put_nilfs(struct the_nilfs *nilfs)
{
	spin_lock(&nilfs_lock);
	if (!atomic_dec_and_test(&nilfs->ns_count)) {
		spin_unlock(&nilfs_lock);
		return;
	}
	list_del_init(&nilfs->ns_list);
	spin_unlock(&nilfs_lock);

	/*
	 * Increment of ns_count never occurs below because the caller
	 * of get_nilfs() holds at least one reference to the_nilfs.
	 * Thus its exclusion control is not required here.
	 */

	might_sleep();
	if (nilfs_loaded(nilfs)) {
		nilfs_mdt_clear(nilfs->ns_sufile);
		nilfs_mdt_destroy(nilfs->ns_sufile);
		nilfs_mdt_clear(nilfs->ns_cpfile);
		nilfs_mdt_destroy(nilfs->ns_cpfile);
		nilfs_mdt_clear(nilfs->ns_dat);
		nilfs_mdt_destroy(nilfs->ns_dat);
		/* XXX: how and when to clear nilfs->ns_gc_dat? */
		nilfs_mdt_destroy(nilfs->ns_gc_dat);
	}
	if (nilfs_init(nilfs)) {
		nilfs_destroy_gccache(nilfs);
		brelse(nilfs->ns_sbh[0]);
		brelse(nilfs->ns_sbh[1]);
	}
	kfree(nilfs);
}