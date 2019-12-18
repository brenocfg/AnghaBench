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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct throtl_grp {TYPE_1__ blkg; int /*<<< orphan*/ * iops; int /*<<< orphan*/ * bps; } ;
struct throtl_data {int dummy; } ;
struct blkio_cgroup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLKIO_POLICY_THROTL ; 
 size_t READ ; 
 size_t WRITE ; 
 int /*<<< orphan*/  __throtl_tg_fill_dev_details (struct throtl_data*,struct throtl_grp*) ; 
 int /*<<< orphan*/  blkcg_get_read_bps (struct blkio_cgroup*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blkcg_get_read_iops (struct blkio_cgroup*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blkcg_get_write_bps (struct blkio_cgroup*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blkcg_get_write_iops (struct blkio_cgroup*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blkiocg_add_blkio_group (struct blkio_cgroup*,TYPE_1__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  throtl_add_group_to_td_list (struct throtl_data*,struct throtl_grp*) ; 

__attribute__((used)) static void throtl_init_add_tg_lists(struct throtl_data *td,
			struct throtl_grp *tg, struct blkio_cgroup *blkcg)
{
	__throtl_tg_fill_dev_details(td, tg);

	/* Add group onto cgroup list */
	blkiocg_add_blkio_group(blkcg, &tg->blkg, (void *)td,
				tg->blkg.dev, BLKIO_POLICY_THROTL);

	tg->bps[READ] = blkcg_get_read_bps(blkcg, tg->blkg.dev);
	tg->bps[WRITE] = blkcg_get_write_bps(blkcg, tg->blkg.dev);
	tg->iops[READ] = blkcg_get_read_iops(blkcg, tg->blkg.dev);
	tg->iops[WRITE] = blkcg_get_write_iops(blkcg, tg->blkg.dev);

	throtl_add_group_to_td_list(td, tg);
}