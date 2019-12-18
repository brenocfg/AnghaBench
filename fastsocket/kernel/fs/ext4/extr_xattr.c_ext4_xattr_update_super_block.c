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
struct super_block {int s_dirt; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_sbh; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT4_FEATURE_COMPAT_EXT_ATTR ; 
 scalar_t__ EXT4_HAS_COMPAT_FEATURE (struct super_block*,int /*<<< orphan*/ ) ; 
 TYPE_1__* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  EXT4_SET_COMPAT_FEATURE (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_handle_dirty_metadata (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_journal_get_write_access (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ext4_xattr_update_super_block(handle_t *handle,
					  struct super_block *sb)
{
	if (EXT4_HAS_COMPAT_FEATURE(sb, EXT4_FEATURE_COMPAT_EXT_ATTR))
		return;

	if (ext4_journal_get_write_access(handle, EXT4_SB(sb)->s_sbh) == 0) {
		EXT4_SET_COMPAT_FEATURE(sb, EXT4_FEATURE_COMPAT_EXT_ATTR);
		sb->s_dirt = 1;
		ext4_handle_dirty_metadata(handle, NULL, EXT4_SB(sb)->s_sbh);
	}
}