#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct autofs_sb_info {TYPE_3__* sb; } ;
struct TYPE_6__ {TYPE_2__* s_root; } ;
struct TYPE_5__ {TYPE_1__* d_inode; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_ino; } ;

/* Variables and functions */

__attribute__((used)) static inline u64 autofs4_get_ino(struct autofs_sb_info *sbi)
{
	return sbi->sb->s_root->d_inode->i_ino;
}