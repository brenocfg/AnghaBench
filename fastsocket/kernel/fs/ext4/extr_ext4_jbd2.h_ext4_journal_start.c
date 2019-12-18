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
struct inode {int /*<<< orphan*/  i_sb; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/ * ext4_journal_start_sb (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline handle_t *ext4_journal_start(struct inode *inode, int nblocks)
{
	return ext4_journal_start_sb(inode->i_sb, nblocks);
}