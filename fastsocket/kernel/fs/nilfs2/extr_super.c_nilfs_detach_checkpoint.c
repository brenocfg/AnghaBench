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
struct the_nilfs {int /*<<< orphan*/  ns_super_sem; } ;
struct nilfs_sb_info {int /*<<< orphan*/  s_list; int /*<<< orphan*/ * s_ifile; struct the_nilfs* s_nilfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nilfs_mdt_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nilfs_mdt_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void nilfs_detach_checkpoint(struct nilfs_sb_info *sbi)
{
	struct the_nilfs *nilfs = sbi->s_nilfs;

	nilfs_mdt_clear(sbi->s_ifile);
	nilfs_mdt_destroy(sbi->s_ifile);
	sbi->s_ifile = NULL;
	down_write(&nilfs->ns_super_sem);
	list_del_init(&sbi->s_list);
	up_write(&nilfs->ns_super_sem);
}