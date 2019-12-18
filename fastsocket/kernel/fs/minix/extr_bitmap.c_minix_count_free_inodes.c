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
struct minix_sb_info {scalar_t__ s_ninodes; int /*<<< orphan*/  s_imap_blocks; int /*<<< orphan*/  s_imap; } ;

/* Variables and functions */
 unsigned long count_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

unsigned long minix_count_free_inodes(struct minix_sb_info *sbi)
{
	return count_free(sbi->s_imap, sbi->s_imap_blocks, sbi->s_ninodes + 1);
}