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
struct super_block {int dummy; } ;
struct inode {int i_state; } ;
struct CodaFid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int I_NEW ; 
 unsigned long coda_f2i (struct CodaFid*) ; 
 int /*<<< orphan*/  coda_test_inode ; 
 struct inode* ilookup5 (struct super_block*,unsigned long,int /*<<< orphan*/ ,struct CodaFid*) ; 
 int /*<<< orphan*/  printk (char*) ; 

struct inode *coda_fid_to_inode(struct CodaFid *fid, struct super_block *sb) 
{
	struct inode *inode;
	unsigned long hash = coda_f2i(fid);

	if ( !sb ) {
		printk("coda_fid_to_inode: no sb!\n");
		return NULL;
	}

	inode = ilookup5(sb, hash, coda_test_inode, fid);
	if ( !inode )
		return NULL;

	/* we should never see newly created inodes because we intentionally
	 * fail in the initialization callback */
	BUG_ON(inode->i_state & I_NEW);

	return inode;
}