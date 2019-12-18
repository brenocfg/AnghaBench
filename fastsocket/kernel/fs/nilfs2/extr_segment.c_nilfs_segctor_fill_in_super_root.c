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
struct the_nilfs {unsigned int ns_inode_size; int /*<<< orphan*/  ns_sufile; int /*<<< orphan*/  ns_cpfile; int /*<<< orphan*/  ns_nongc_ctime; } ;
struct nilfs_super_root {scalar_t__ sr_flags; int /*<<< orphan*/  sr_nongc_ctime; int /*<<< orphan*/  sr_bytes; } ;
struct nilfs_sc_info {int /*<<< orphan*/  sc_seg_ctime; struct buffer_head* sc_super_root; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  NILFS_SR_BYTES ; 
 int /*<<< orphan*/  NILFS_SR_CPFILE_OFFSET (unsigned int) ; 
 int /*<<< orphan*/  NILFS_SR_DAT_OFFSET (unsigned int) ; 
 int /*<<< orphan*/  NILFS_SR_SUFILE_OFFSET (unsigned int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_dat_inode (struct the_nilfs*) ; 
 scalar_t__ nilfs_doing_gc () ; 
 int /*<<< orphan*/  nilfs_mdt_write_inode_direct (int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nilfs_segctor_fill_in_super_root(struct nilfs_sc_info *sci,
					     struct the_nilfs *nilfs)
{
	struct buffer_head *bh_sr = sci->sc_super_root;
	struct nilfs_super_root *raw_sr =
		(struct nilfs_super_root *)bh_sr->b_data;
	unsigned isz = nilfs->ns_inode_size;

	raw_sr->sr_bytes = cpu_to_le16(NILFS_SR_BYTES);
	raw_sr->sr_nongc_ctime
		= cpu_to_le64(nilfs_doing_gc() ?
			      nilfs->ns_nongc_ctime : sci->sc_seg_ctime);
	raw_sr->sr_flags = 0;

	nilfs_mdt_write_inode_direct(
		nilfs_dat_inode(nilfs), bh_sr, NILFS_SR_DAT_OFFSET(isz));
	nilfs_mdt_write_inode_direct(
		nilfs->ns_cpfile, bh_sr, NILFS_SR_CPFILE_OFFSET(isz));
	nilfs_mdt_write_inode_direct(
		nilfs->ns_sufile, bh_sr, NILFS_SR_SUFILE_OFFSET(isz));
}