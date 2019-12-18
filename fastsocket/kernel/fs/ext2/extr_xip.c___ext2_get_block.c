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
struct buffer_head {int /*<<< orphan*/  b_blocknr; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENODATA ; 
 int ext2_get_block (struct inode*,int /*<<< orphan*/ ,struct buffer_head*,int) ; 
 int /*<<< orphan*/  memset (struct buffer_head*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int
__ext2_get_block(struct inode *inode, pgoff_t pgoff, int create,
		   sector_t *result)
{
	struct buffer_head tmp;
	int rc;

	memset(&tmp, 0, sizeof(struct buffer_head));
	rc = ext2_get_block(inode, pgoff, &tmp, create);
	*result = tmp.b_blocknr;

	/* did we get a sparse block (hole in the file)? */
	if (!tmp.b_blocknr && !rc) {
		BUG_ON(create);
		rc = -ENODATA;
	}

	return rc;
}