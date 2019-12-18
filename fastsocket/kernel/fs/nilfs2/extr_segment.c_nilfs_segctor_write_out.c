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
struct nilfs_transaction_info {int dummy; } ;
struct nilfs_segctor_req {int /*<<< orphan*/  mode; } ;
struct nilfs_sc_info {struct nilfs_sb_info* sc_sbi; } ;
struct nilfs_sb_info {int dummy; } ;

/* Variables and functions */
 int NILFS_SC_CLEANUP_RETRY ; 
 int /*<<< orphan*/  SC_LSEG_SR ; 
 int /*<<< orphan*/  nilfs_segctor_accept (struct nilfs_sc_info*,struct nilfs_segctor_req*) ; 
 int nilfs_segctor_construct (struct nilfs_sc_info*,struct nilfs_segctor_req*) ; 
 int /*<<< orphan*/  nilfs_segctor_notify (struct nilfs_sc_info*,struct nilfs_segctor_req*) ; 
 int /*<<< orphan*/  nilfs_transaction_lock (struct nilfs_sb_info*,struct nilfs_transaction_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_transaction_unlock (struct nilfs_sb_info*) ; 

__attribute__((used)) static void nilfs_segctor_write_out(struct nilfs_sc_info *sci)
{
	int ret, retrycount = NILFS_SC_CLEANUP_RETRY;

	/* The segctord thread was stopped and its timer was removed.
	   But some tasks remain. */
	do {
		struct nilfs_sb_info *sbi = sci->sc_sbi;
		struct nilfs_transaction_info ti;
		struct nilfs_segctor_req req = { .mode = SC_LSEG_SR };

		nilfs_transaction_lock(sbi, &ti, 0);
		nilfs_segctor_accept(sci, &req);
		ret = nilfs_segctor_construct(sci, &req);
		nilfs_segctor_notify(sci, &req);
		nilfs_transaction_unlock(sbi);

	} while (ret && retrycount-- > 0);
}