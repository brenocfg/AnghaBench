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
struct treepath {int dummy; } ;
struct item_head {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_I_PITEM (struct buffer_head*,struct item_head*) ; 
 int /*<<< orphan*/  INODE_PKEY (struct inode*) ; 
 struct item_head* PATH_PITEM_HEAD (struct treepath*) ; 
 struct buffer_head* PATH_PLAST_BUFFER (struct treepath*) ; 
 int /*<<< orphan*/  inode2sd (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode2sd_v1 (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_statdata_le_ih (struct item_head*) ; 
 int /*<<< orphan*/  reiserfs_panic (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,struct item_head*) ; 
 scalar_t__ stat_data_v1 (struct item_head*) ; 

__attribute__((used)) static void update_stat_data(struct treepath *path, struct inode *inode,
			     loff_t size)
{
	struct buffer_head *bh;
	struct item_head *ih;

	bh = PATH_PLAST_BUFFER(path);
	ih = PATH_PITEM_HEAD(path);

	if (!is_statdata_le_ih(ih))
		reiserfs_panic(inode->i_sb, "vs-13065", "key %k, found item %h",
			       INODE_PKEY(inode), ih);

	if (stat_data_v1(ih)) {
		// path points to old stat data
		inode2sd_v1(B_I_PITEM(bh, ih), inode, size);
	} else {
		inode2sd(B_I_PITEM(bh, ih), inode, size);
	}

	return;
}