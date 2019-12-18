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
struct inomap {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct TYPE_2__ {struct inomap* i_imap; } ;

/* Variables and functions */
 TYPE_1__* JFS_IP (struct inode*) ; 
 int /*<<< orphan*/  diSync (struct inode*) ; 
 scalar_t__ isReadOnly (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct inomap*) ; 
 int /*<<< orphan*/  truncate_inode_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int diUnmount(struct inode *ipimap, int mounterror)
{
	struct inomap *imap = JFS_IP(ipimap)->i_imap;

	/*
	 * update the on-disk inode map control structure
	 */

	if (!(mounterror || isReadOnly(ipimap)))
		diSync(ipimap);

	/*
	 * Invalidate the page cache buffers
	 */
	truncate_inode_pages(ipimap->i_mapping, 0);

	/*
	 * free in-memory control structure
	 */
	kfree(imap);

	return (0);
}