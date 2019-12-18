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
struct inode {int /*<<< orphan*/  i_ino; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  UFSD (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  ll_rw_block (int /*<<< orphan*/ ,int,struct buffer_head**) ; 
 struct buffer_head* ufs_getfrag (struct inode*,unsigned int,int,int*) ; 
 int /*<<< orphan*/  wait_on_buffer (struct buffer_head*) ; 

struct buffer_head * ufs_bread (struct inode * inode, unsigned fragment,
	int create, int * err)
{
	struct buffer_head * bh;

	UFSD("ENTER, ino %lu, fragment %u\n", inode->i_ino, fragment);
	bh = ufs_getfrag (inode, fragment, create, err);
	if (!bh || buffer_uptodate(bh)) 		
		return bh;
	ll_rw_block (READ, 1, &bh);
	wait_on_buffer (bh);
	if (buffer_uptodate(bh))
		return bh;
	brelse (bh);
	*err = -EIO;
	return NULL;
}