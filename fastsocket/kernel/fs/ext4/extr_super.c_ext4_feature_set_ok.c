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
typedef  int /*<<< orphan*/  u64 ;
struct super_block {int dummy; } ;
typedef  int /*<<< orphan*/  blkcnt_t ;
struct TYPE_4__ {TYPE_1__* s_es; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_feature_ro_compat; int /*<<< orphan*/  s_feature_incompat; } ;

/* Variables and functions */
 int EXT4_FEATURE_INCOMPAT_SUPP ; 
 int EXT4_FEATURE_RO_COMPAT_HUGE_FILE ; 
 int EXT4_FEATURE_RO_COMPAT_SUPP ; 
 scalar_t__ EXT4_HAS_INCOMPAT_FEATURE (struct super_block*,int) ; 
 scalar_t__ EXT4_HAS_RO_COMPAT_FEATURE (struct super_block*,int) ; 
 TYPE_2__* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  ext4_msg (struct super_block*,int /*<<< orphan*/ ,char*,...) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_feature_set_ok(struct super_block *sb, int readonly)
{
	if (EXT4_HAS_INCOMPAT_FEATURE(sb, ~EXT4_FEATURE_INCOMPAT_SUPP)) {
		ext4_msg(sb, KERN_ERR,
			"Couldn't mount because of "
			"unsupported optional features (%x)",
			(le32_to_cpu(EXT4_SB(sb)->s_es->s_feature_incompat) &
			~EXT4_FEATURE_INCOMPAT_SUPP));
		return 0;
	}

	if (readonly)
		return 1;

	/* Check that feature set is OK for a read-write mount */
	if (EXT4_HAS_RO_COMPAT_FEATURE(sb, ~EXT4_FEATURE_RO_COMPAT_SUPP)) {
		ext4_msg(sb, KERN_ERR, "couldn't mount RDWR because of "
			 "unsupported optional features (%x)",
			 (le32_to_cpu(EXT4_SB(sb)->s_es->s_feature_ro_compat) &
				~EXT4_FEATURE_RO_COMPAT_SUPP));
		return 0;
	}
	/*
	 * Large file size enabled file system can only be mounted
	 * read-write on 32-bit systems if kernel is built with CONFIG_LBDAF
	 */
	if (EXT4_HAS_RO_COMPAT_FEATURE(sb, EXT4_FEATURE_RO_COMPAT_HUGE_FILE)) {
		if (sizeof(blkcnt_t) < sizeof(u64)) {
			ext4_msg(sb, KERN_ERR, "Filesystem with huge files "
				 "cannot be mounted RDWR without "
				 "CONFIG_LBDAF");
			return 0;
		}
	}
	return 1;
}