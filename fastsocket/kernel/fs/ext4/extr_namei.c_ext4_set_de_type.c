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
typedef  size_t umode_t ;
struct super_block {int dummy; } ;
struct ext4_dir_entry_2 {int /*<<< orphan*/  file_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT4_FEATURE_INCOMPAT_FILETYPE ; 
 scalar_t__ EXT4_HAS_INCOMPAT_FEATURE (struct super_block*,int /*<<< orphan*/ ) ; 
 size_t S_IFMT ; 
 size_t S_SHIFT ; 
 int /*<<< orphan*/ * ext4_type_by_mode ; 

__attribute__((used)) static inline void ext4_set_de_type(struct super_block *sb,
				struct ext4_dir_entry_2 *de,
				umode_t mode) {
	if (EXT4_HAS_INCOMPAT_FEATURE(sb, EXT4_FEATURE_INCOMPAT_FILETYPE))
		de->file_type = ext4_type_by_mode[(mode & S_IFMT)>>S_SHIFT];
}