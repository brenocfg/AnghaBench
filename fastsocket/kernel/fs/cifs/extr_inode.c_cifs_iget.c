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
struct super_block {int s_flags; } ;
struct inode {int i_flags; int i_state; unsigned long i_ino; } ;
struct cifs_fattr {int cf_flags; int /*<<< orphan*/  cf_uniqueid; } ;
struct TYPE_2__ {int /*<<< orphan*/ * fscache; } ;

/* Variables and functions */
 int CIFS_FATTR_INO_COLLISION ; 
 TYPE_1__* CIFS_I (struct inode*) ; 
 int /*<<< orphan*/  CIFS_SB (struct super_block*) ; 
 int I_NEW ; 
 int MS_NOATIME ; 
 int /*<<< orphan*/  ROOT_I ; 
 int S_NOATIME ; 
 int S_NOCMTIME ; 
 int /*<<< orphan*/  cFYI (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cifs_autodisable_serverino (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cifs_fattr_to_inode (struct inode*,struct cifs_fattr*) ; 
 int /*<<< orphan*/  cifs_find_inode ; 
 int /*<<< orphan*/  cifs_init_inode ; 
 unsigned long cifs_uniqueid_to_ino_t (int /*<<< orphan*/ ) ; 
 struct inode* iget5_locked (struct super_block*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cifs_fattr*) ; 
 scalar_t__ inode_has_hashed_dentries (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  iunique (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

struct inode *
cifs_iget(struct super_block *sb, struct cifs_fattr *fattr)
{
	unsigned long hash;
	struct inode *inode;

retry_iget5_locked:
	cFYI(1, "looking for uniqueid=%llu", fattr->cf_uniqueid);

	/* hash down to 32-bits on 32-bit arch */
	hash = cifs_uniqueid_to_ino_t(fattr->cf_uniqueid);

	inode = iget5_locked(sb, hash, cifs_find_inode, cifs_init_inode, fattr);
	if (inode) {
		/* was there a potentially problematic inode collision? */
		if (fattr->cf_flags & CIFS_FATTR_INO_COLLISION) {
			fattr->cf_flags &= ~CIFS_FATTR_INO_COLLISION;

			if (inode_has_hashed_dentries(inode)) {
				cifs_autodisable_serverino(CIFS_SB(sb));
				iput(inode);
				fattr->cf_uniqueid = iunique(sb, ROOT_I);
				goto retry_iget5_locked;
			}
		}

		cifs_fattr_to_inode(inode, fattr);
		if (sb->s_flags & MS_NOATIME)
			inode->i_flags |= S_NOATIME | S_NOCMTIME;
		if (inode->i_state & I_NEW) {
			inode->i_ino = hash;
#ifdef CONFIG_CIFS_FSCACHE
			/* initialize per-inode cache cookie pointer */
			CIFS_I(inode)->fscache = NULL;
#endif
			unlock_new_inode(inode);
		}
	}

	return inode;
}