#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct writeback_control {int dummy; } ;
struct nfs_pageio_descriptor {int pg_error; } ;
struct inode {int dummy; } ;
struct address_space {struct inode* host; } ;
struct TYPE_4__ {unsigned long flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* write_pageio_init ) (struct nfs_pageio_descriptor*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NFSIOS_VFSWRITEPAGES ; 
 TYPE_2__* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  NFS_INO_FLUSHING ; 
 TYPE_1__* NFS_PROTO (struct inode*) ; 
 int /*<<< orphan*/  TASK_KILLABLE ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  nfs_async_write_completion_ops ; 
 int /*<<< orphan*/  nfs_inc_stats (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_pageio_complete (struct nfs_pageio_descriptor*) ; 
 int /*<<< orphan*/  nfs_wait_bit_killable ; 
 int /*<<< orphan*/  nfs_writepages_callback ; 
 int /*<<< orphan*/  smp_mb__after_clear_bit () ; 
 int /*<<< orphan*/  stub1 (struct nfs_pageio_descriptor*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wait_on_bit_lock (unsigned long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_bit (unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wb_priority (struct writeback_control*) ; 
 int write_cache_pages (struct address_space*,struct writeback_control*,int /*<<< orphan*/ ,struct nfs_pageio_descriptor*) ; 

int nfs_writepages(struct address_space *mapping, struct writeback_control *wbc)
{
	struct inode *inode = mapping->host;
	unsigned long *bitlock = &NFS_I(inode)->flags;
	struct nfs_pageio_descriptor pgio;
	int err;

	/* Stop dirtying of new pages while we sync */
	err = wait_on_bit_lock(bitlock, NFS_INO_FLUSHING,
			nfs_wait_bit_killable, TASK_KILLABLE);
	if (err)
		goto out_err;

	nfs_inc_stats(inode, NFSIOS_VFSWRITEPAGES);

	NFS_PROTO(inode)->write_pageio_init(&pgio, inode, wb_priority(wbc), &nfs_async_write_completion_ops);
	err = write_cache_pages(mapping, wbc, nfs_writepages_callback, &pgio);
	nfs_pageio_complete(&pgio);

	clear_bit_unlock(NFS_INO_FLUSHING, bitlock);
	smp_mb__after_clear_bit();
	wake_up_bit(bitlock, NFS_INO_FLUSHING);

	if (err < 0)
		goto out_err;
	err = pgio.pg_error;
	if (err < 0)
		goto out_err;
	return 0;
out_err:
	return err;
}