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
struct inode {unsigned long i_ino; } ;
struct CodaFid {int dummy; } ;
struct coda_inode_info {struct CodaFid c_fid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct coda_inode_info* ITOC (struct inode*) ; 
 int /*<<< orphan*/  __insert_inode_hash (struct inode*,unsigned long) ; 
 unsigned long coda_f2i (struct CodaFid*) ; 
 int /*<<< orphan*/  coda_fideq (struct CodaFid*,struct CodaFid*) ; 
 int /*<<< orphan*/  remove_inode_hash (struct inode*) ; 

void coda_replace_fid(struct inode *inode, struct CodaFid *oldfid, 
		      struct CodaFid *newfid)
{
	struct coda_inode_info *cii;
	unsigned long hash = coda_f2i(newfid);
	
	cii = ITOC(inode);

	BUG_ON(!coda_fideq(&cii->c_fid, oldfid));

	/* replace fid and rehash inode */
	/* XXX we probably need to hold some lock here! */
	remove_inode_hash(inode);
	cii->c_fid = *newfid;
	inode->i_ino = hash;
	__insert_inode_hash(inode, hash);
}