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
struct buffer_head {int dummy; } ;
struct block_device {int dummy; } ;
typedef  scalar_t__ b_blocknr_t ;

/* Variables and functions */
 int BUFNR ; 
 int /*<<< orphan*/  READ ; 
 struct buffer_head* __getblk (struct block_device*,scalar_t__,int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  ll_rw_block (int /*<<< orphan*/ ,int,struct buffer_head**) ; 
 int /*<<< orphan*/  wait_on_buffer (struct buffer_head*) ; 

__attribute__((used)) static struct buffer_head *reiserfs_breada(struct block_device *dev,
					   b_blocknr_t block, int bufsize,
					   b_blocknr_t max_block)
{
	struct buffer_head *bhlist[BUFNR];
	unsigned int blocks = BUFNR;
	struct buffer_head *bh;
	int i, j;

	bh = __getblk(dev, block, bufsize);
	if (buffer_uptodate(bh))
		return (bh);

	if (block + BUFNR > max_block) {
		blocks = max_block - block;
	}
	bhlist[0] = bh;
	j = 1;
	for (i = 1; i < blocks; i++) {
		bh = __getblk(dev, block + i, bufsize);
		if (buffer_uptodate(bh)) {
			brelse(bh);
			break;
		} else
			bhlist[j++] = bh;
	}
	ll_rw_block(READ, j, bhlist);
	for (i = 1; i < j; i++)
		brelse(bhlist[i]);
	bh = bhlist[0];
	wait_on_buffer(bh);
	if (buffer_uptodate(bh))
		return bh;
	brelse(bh);
	return NULL;
}