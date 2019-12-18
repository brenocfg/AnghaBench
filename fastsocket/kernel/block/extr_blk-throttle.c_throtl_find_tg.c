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
struct throtl_grp {int dummy; } ;
struct throtl_data {struct throtl_grp* root_tg; } ;
struct blkio_cgroup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __throtl_tg_fill_dev_details (struct throtl_data*,struct throtl_grp*) ; 
 struct blkio_cgroup blkio_root_cgroup ; 
 int /*<<< orphan*/  blkiocg_lookup_group (struct blkio_cgroup*,void*) ; 
 struct throtl_grp* tg_of_blkg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct
throtl_grp *throtl_find_tg(struct throtl_data *td, struct blkio_cgroup *blkcg)
{
	struct throtl_grp *tg = NULL;
	void *key = td;

	/*
	 * This is the common case when there are no blkio cgroups.
 	 * Avoid lookup in this case
 	 */
	if (blkcg == &blkio_root_cgroup)
		tg = td->root_tg;
	else
		tg = tg_of_blkg(blkiocg_lookup_group(blkcg, key));

	__throtl_tg_fill_dev_details(td, tg);
	return tg;
}