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
struct the_nilfs {unsigned int ns_inode_size; void* ns_dat; void* ns_gc_dat; void* ns_cpfile; void* ns_sufile; int /*<<< orphan*/  ns_nongc_ctime; int /*<<< orphan*/  ns_sem; struct nilfs_super_block** ns_sbp; } ;
struct nilfs_super_root {int /*<<< orphan*/  sr_nongc_ctime; } ;
struct nilfs_super_block {int /*<<< orphan*/  s_segment_usage_size; int /*<<< orphan*/  s_checkpoint_size; int /*<<< orphan*/  s_dat_entry_size; } ;
struct nilfs_sufile_header {int dummy; } ;
struct nilfs_sb_info {int /*<<< orphan*/  s_super; } ;
struct nilfs_cpfile_header {int dummy; } ;
struct lock_class_key {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_2__ {int /*<<< orphan*/  mi_sem; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NILFS_CPFILE_INO ; 
 int /*<<< orphan*/  NILFS_DAT_INO ; 
 TYPE_1__* NILFS_MDT (void*) ; 
 int /*<<< orphan*/  NILFS_SR_CPFILE_OFFSET (unsigned int) ; 
 int /*<<< orphan*/  NILFS_SR_DAT_OFFSET (unsigned int) ; 
 int /*<<< orphan*/  NILFS_SR_SUFILE_OFFSET (unsigned int) ; 
 int /*<<< orphan*/  NILFS_SUFILE_INO ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_set_class (int /*<<< orphan*/ *,struct lock_class_key*) ; 
 int /*<<< orphan*/  nilfs_mdt_destroy (void*) ; 
 void* nilfs_mdt_new (struct the_nilfs*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nilfs_mdt_read_inode_direct (void*,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_mdt_set_entry_size (void*,unsigned int,int) ; 
 int /*<<< orphan*/  nilfs_mdt_set_shadow (void*,void*) ; 
 int nilfs_palloc_init_blockgroup (void*,unsigned int) ; 
 int nilfs_read_super_root_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer_head**,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nilfs_load_super_root(struct the_nilfs *nilfs,
				 struct nilfs_sb_info *sbi, sector_t sr_block)
{
	static struct lock_class_key dat_lock_key;
	struct buffer_head *bh_sr;
	struct nilfs_super_root *raw_sr;
	struct nilfs_super_block **sbp = nilfs->ns_sbp;
	unsigned dat_entry_size, segment_usage_size, checkpoint_size;
	unsigned inode_size;
	int err;

	err = nilfs_read_super_root_block(sbi->s_super, sr_block, &bh_sr, 1);
	if (unlikely(err))
		return err;

	down_read(&nilfs->ns_sem);
	dat_entry_size = le16_to_cpu(sbp[0]->s_dat_entry_size);
	checkpoint_size = le16_to_cpu(sbp[0]->s_checkpoint_size);
	segment_usage_size = le16_to_cpu(sbp[0]->s_segment_usage_size);
	up_read(&nilfs->ns_sem);

	inode_size = nilfs->ns_inode_size;

	err = -ENOMEM;
	nilfs->ns_dat = nilfs_mdt_new(nilfs, NULL, NILFS_DAT_INO);
	if (unlikely(!nilfs->ns_dat))
		goto failed;

	nilfs->ns_gc_dat = nilfs_mdt_new(nilfs, NULL, NILFS_DAT_INO);
	if (unlikely(!nilfs->ns_gc_dat))
		goto failed_dat;

	nilfs->ns_cpfile = nilfs_mdt_new(nilfs, NULL, NILFS_CPFILE_INO);
	if (unlikely(!nilfs->ns_cpfile))
		goto failed_gc_dat;

	nilfs->ns_sufile = nilfs_mdt_new(nilfs, NULL, NILFS_SUFILE_INO);
	if (unlikely(!nilfs->ns_sufile))
		goto failed_cpfile;

	err = nilfs_palloc_init_blockgroup(nilfs->ns_dat, dat_entry_size);
	if (unlikely(err))
		goto failed_sufile;

	err = nilfs_palloc_init_blockgroup(nilfs->ns_gc_dat, dat_entry_size);
	if (unlikely(err))
		goto failed_sufile;

	lockdep_set_class(&NILFS_MDT(nilfs->ns_dat)->mi_sem, &dat_lock_key);
	lockdep_set_class(&NILFS_MDT(nilfs->ns_gc_dat)->mi_sem, &dat_lock_key);

	nilfs_mdt_set_shadow(nilfs->ns_dat, nilfs->ns_gc_dat);
	nilfs_mdt_set_entry_size(nilfs->ns_cpfile, checkpoint_size,
				 sizeof(struct nilfs_cpfile_header));
	nilfs_mdt_set_entry_size(nilfs->ns_sufile, segment_usage_size,
				 sizeof(struct nilfs_sufile_header));

	err = nilfs_mdt_read_inode_direct(
		nilfs->ns_dat, bh_sr, NILFS_SR_DAT_OFFSET(inode_size));
	if (unlikely(err))
		goto failed_sufile;

	err = nilfs_mdt_read_inode_direct(
		nilfs->ns_cpfile, bh_sr, NILFS_SR_CPFILE_OFFSET(inode_size));
	if (unlikely(err))
		goto failed_sufile;

	err = nilfs_mdt_read_inode_direct(
		nilfs->ns_sufile, bh_sr, NILFS_SR_SUFILE_OFFSET(inode_size));
	if (unlikely(err))
		goto failed_sufile;

	raw_sr = (struct nilfs_super_root *)bh_sr->b_data;
	nilfs->ns_nongc_ctime = le64_to_cpu(raw_sr->sr_nongc_ctime);

 failed:
	brelse(bh_sr);
	return err;

 failed_sufile:
	nilfs_mdt_destroy(nilfs->ns_sufile);

 failed_cpfile:
	nilfs_mdt_destroy(nilfs->ns_cpfile);

 failed_gc_dat:
	nilfs_mdt_destroy(nilfs->ns_gc_dat);

 failed_dat:
	nilfs_mdt_destroy(nilfs->ns_dat);
	goto failed;
}