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
struct inode {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME_SEC ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int qnx4_block_map (struct inode*,int) ; 
 int /*<<< orphan*/  qnx4_free_block (int /*<<< orphan*/ ,int) ; 
 int qnx4_new_block (int /*<<< orphan*/ ) ; 
 struct buffer_head* sb_getblk (int /*<<< orphan*/ ,int) ; 
 int tmp ; 
 int tst ; 

__attribute__((used)) static struct buffer_head *qnx4_getblk(struct inode *inode, int nr,
				       int create)
{
	struct buffer_head *result = NULL;

	if ( nr >= 0 )
		nr = qnx4_block_map( inode, nr );
	if (nr) {
		result = sb_getblk(inode->i_sb, nr);
		return result;
	}
	if (!create) {
		return NULL;
	}
#if 0
	tmp = qnx4_new_block(inode->i_sb);
	if (!tmp) {
		return NULL;
	}
	result = sb_getblk(inode->i_sb, tmp);
	if (tst) {
		qnx4_free_block(inode->i_sb, tmp);
		brelse(result);
		goto repeat;
	}
	tst = tmp;
#endif
	inode->i_ctime = CURRENT_TIME_SEC;
	mark_inode_dirty(inode);
	return result;
}