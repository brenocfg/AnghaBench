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
struct super_block {int dummy; } ;
struct reiserfs_super_block {int /*<<< orphan*/  s_flags; } ;
struct TYPE_2__ {int s_mount_opt; } ;

/* Variables and functions */
 int REISERFS_ATTRS ; 
 TYPE_1__* REISERFS_SB (struct super_block*) ; 
 struct reiserfs_super_block* SB_DISK_SUPER_BLOCK (struct super_block*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ old_format_only (struct super_block*) ; 
 scalar_t__ reiserfs_attrs (struct super_block*) ; 
 int reiserfs_attrs_cleared ; 
 int /*<<< orphan*/  reiserfs_warning (struct super_block*,char*,char*) ; 

__attribute__((used)) static void handle_attrs(struct super_block *s)
{
	struct reiserfs_super_block *rs = SB_DISK_SUPER_BLOCK(s);

	if (reiserfs_attrs(s)) {
		if (old_format_only(s)) {
			reiserfs_warning(s, "super-6517", "cannot support "
					 "attributes on 3.5.x disk format");
			REISERFS_SB(s)->s_mount_opt &= ~(1 << REISERFS_ATTRS);
			return;
		}
		if (!(le32_to_cpu(rs->s_flags) & reiserfs_attrs_cleared)) {
			reiserfs_warning(s, "super-6518", "cannot support "
					 "attributes until flag is set in "
					 "super-block");
			REISERFS_SB(s)->s_mount_opt &= ~(1 << REISERFS_ATTRS);
		}
	}
}