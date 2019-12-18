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
struct inode {TYPE_1__* i_sb; } ;
struct buffer_head {int b_blocknr; int /*<<< orphan*/  b_data; scalar_t__ b_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_blocksize; } ;

/* Variables and functions */
 scalar_t__ buffer_mapped (struct buffer_head*) ; 
 scalar_t__ buffer_new (struct buffer_head*) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct buffer_head* sb_getblk (TYPE_1__*,int) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 int ufs_getfrag_block (struct inode*,unsigned int,struct buffer_head*,int) ; 

__attribute__((used)) static struct buffer_head *ufs_getfrag(struct inode *inode,
				       unsigned int fragment,
				       int create, int *err)
{
	struct buffer_head dummy;
	int error;

	dummy.b_state = 0;
	dummy.b_blocknr = -1000;
	error = ufs_getfrag_block(inode, fragment, &dummy, create);
	*err = error;
	if (!error && buffer_mapped(&dummy)) {
		struct buffer_head *bh;
		bh = sb_getblk(inode->i_sb, dummy.b_blocknr);
		if (buffer_new(&dummy)) {
			memset(bh->b_data, 0, inode->i_sb->s_blocksize);
			set_buffer_uptodate(bh);
			mark_buffer_dirty(bh);
		}
		return bh;
	}
	return NULL;
}