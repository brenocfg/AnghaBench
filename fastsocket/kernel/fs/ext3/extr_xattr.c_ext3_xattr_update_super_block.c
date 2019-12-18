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
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_sbh; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT3_FEATURE_COMPAT_EXT_ATTR ; 
 scalar_t__ EXT3_HAS_COMPAT_FEATURE (struct super_block*,int /*<<< orphan*/ ) ; 
 TYPE_1__* EXT3_SB (struct super_block*) ; 
 int /*<<< orphan*/  EXT3_SET_COMPAT_FEATURE (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext3_journal_dirty_metadata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ext3_journal_get_write_access (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ext3_xattr_update_super_block(handle_t *handle,
					  struct super_block *sb)
{
	if (EXT3_HAS_COMPAT_FEATURE(sb, EXT3_FEATURE_COMPAT_EXT_ATTR))
		return;

	if (ext3_journal_get_write_access(handle, EXT3_SB(sb)->s_sbh) == 0) {
		EXT3_SET_COMPAT_FEATURE(sb, EXT3_FEATURE_COMPAT_EXT_ATTR);
		ext3_journal_dirty_metadata(handle, EXT3_SB(sb)->s_sbh);
	}
}