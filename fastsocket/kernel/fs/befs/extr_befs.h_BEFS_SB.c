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
struct super_block {scalar_t__ s_fs_info; } ;
typedef  int /*<<< orphan*/  befs_sb_info ;

/* Variables and functions */

__attribute__((used)) static inline befs_sb_info *
BEFS_SB(const struct super_block *super)
{
	return (befs_sb_info *) super->s_fs_info;
}