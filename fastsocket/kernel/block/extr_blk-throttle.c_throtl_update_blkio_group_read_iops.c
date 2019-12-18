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
struct throtl_grp {unsigned int* iops; } ;
struct throtl_data {int dummy; } ;
struct blkio_group {int dummy; } ;

/* Variables and functions */
 size_t READ ; 
 struct throtl_grp* tg_of_blkg (struct blkio_group*) ; 
 int /*<<< orphan*/  throtl_update_blkio_group_common (struct throtl_data*,struct throtl_grp*) ; 

__attribute__((used)) static void throtl_update_blkio_group_read_iops(void *key,
			struct blkio_group *blkg, unsigned int read_iops)
{
	struct throtl_data *td = key;
	struct throtl_grp *tg = tg_of_blkg(blkg);

	tg->iops[READ] = read_iops;
	throtl_update_blkio_group_common(td, tg);
}