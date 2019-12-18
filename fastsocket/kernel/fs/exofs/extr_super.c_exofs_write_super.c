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
struct super_block {int s_flags; scalar_t__ s_dirt; } ;

/* Variables and functions */
 int MS_RDONLY ; 
 int /*<<< orphan*/  exofs_sync_fs (struct super_block*,int) ; 

__attribute__((used)) static void exofs_write_super(struct super_block *sb)
{
	if (!(sb->s_flags & MS_RDONLY))
		exofs_sync_fs(sb, 1);
	else
		sb->s_dirt = 0;
}