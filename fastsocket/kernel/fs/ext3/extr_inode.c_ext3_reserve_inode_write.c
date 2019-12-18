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
struct ext3_iloc {int /*<<< orphan*/ * bh; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ *) ; 
 int ext3_get_inode_loc (struct inode*,struct ext3_iloc*) ; 
 int ext3_journal_get_write_access (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext3_std_error (int /*<<< orphan*/ ,int) ; 

int
ext3_reserve_inode_write(handle_t *handle, struct inode *inode,
			 struct ext3_iloc *iloc)
{
	int err = 0;
	if (handle) {
		err = ext3_get_inode_loc(inode, iloc);
		if (!err) {
			BUFFER_TRACE(iloc->bh, "get_write_access");
			err = ext3_journal_get_write_access(handle, iloc->bh);
			if (err) {
				brelse(iloc->bh);
				iloc->bh = NULL;
			}
		}
	}
	ext3_std_error(inode->i_sb, err);
	return err;
}