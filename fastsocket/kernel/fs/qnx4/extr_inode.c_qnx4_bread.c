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
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  ll_rw_block (int /*<<< orphan*/ ,int,struct buffer_head**) ; 
 struct buffer_head* qnx4_getblk (struct inode*,int,int) ; 
 int /*<<< orphan*/  wait_on_buffer (struct buffer_head*) ; 

struct buffer_head *qnx4_bread(struct inode *inode, int block, int create)
{
	struct buffer_head *bh;

	bh = qnx4_getblk(inode, block, create);
	if (!bh || buffer_uptodate(bh)) {
		return bh;
	}
	ll_rw_block(READ, 1, &bh);
	wait_on_buffer(bh);
	if (buffer_uptodate(bh)) {
		return bh;
	}
	brelse(bh);

	return NULL;
}