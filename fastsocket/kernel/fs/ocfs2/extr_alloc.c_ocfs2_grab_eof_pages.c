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
struct page {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
typedef  int loff_t ;
struct TYPE_2__ {int s_clustersize_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 TYPE_1__* OCFS2_SB (struct super_block*) ; 
 int ocfs2_grab_pages (struct inode*,int,int,struct page**,int*) ; 

__attribute__((used)) static int ocfs2_grab_eof_pages(struct inode *inode, loff_t start, loff_t end,
				struct page **pages, int *num)
{
	struct super_block *sb = inode->i_sb;

	BUG_ON(start >> OCFS2_SB(sb)->s_clustersize_bits !=
	       (end - 1) >> OCFS2_SB(sb)->s_clustersize_bits);

	return ocfs2_grab_pages(inode, start, end, pages, num);
}