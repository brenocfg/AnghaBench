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
struct nfs_io_counter {int /*<<< orphan*/  flags; int /*<<< orphan*/  io_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_IO_INPROGRESS ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_clear_bit () ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nfs_iocounter_dec(struct nfs_io_counter *c)
{
	if (atomic_dec_and_test(&c->io_count)) {
		clear_bit(NFS_IO_INPROGRESS, &c->flags);
		smp_mb__after_clear_bit();
		wake_up_bit(&c->flags, NFS_IO_INPROGRESS);
	}
}