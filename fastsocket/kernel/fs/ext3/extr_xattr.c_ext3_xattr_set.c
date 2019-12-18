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
 int ENOSPC ; 
 int /*<<< orphan*/  EXT3_DATA_TRANS_BLOCKS (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ext3_journal_start (struct inode*,int /*<<< orphan*/ ) ; 
 int ext3_journal_stop (int /*<<< orphan*/ *) ; 
 scalar_t__ ext3_should_retry_alloc (int /*<<< orphan*/ ,int*) ; 
 int ext3_xattr_set_handle (int /*<<< orphan*/ *,struct inode*,int,char const*,void const*,size_t,int) ; 

int
ext3_xattr_set(struct inode *inode, int name_index, const char *name,
	       const void *value, size_t value_len, int flags)
{
	handle_t *handle;
	int error, retries = 0;

retry:
	handle = ext3_journal_start(inode, EXT3_DATA_TRANS_BLOCKS(inode->i_sb));
	if (IS_ERR(handle)) {
		error = PTR_ERR(handle);
	} else {
		int error2;

		error = ext3_xattr_set_handle(handle, inode, name_index, name,
					      value, value_len, flags);
		error2 = ext3_journal_stop(handle);
		if (error == -ENOSPC &&
		    ext3_should_retry_alloc(inode->i_sb, &retries))
			goto retry;
		if (error == 0)
			error = error2;
	}

	return error;
}