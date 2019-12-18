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
struct superblock_smack {int smk_initialized; char* smk_hat; char* smk_floor; char* smk_default; char* smk_root; int /*<<< orphan*/  smk_sblock; } ;
struct super_block {struct superblock_smack* s_security; struct dentry* s_root; } ;
struct inode_smack {char* smk_inode; } ;
struct inode {struct inode_smack* i_security; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMK_FSDEFAULT ; 
 int /*<<< orphan*/  SMK_FSFLOOR ; 
 int /*<<< orphan*/  SMK_FSHAT ; 
 int /*<<< orphan*/  SMK_FSROOT ; 
 struct inode_smack* new_inode_smack (char*) ; 
 char* smk_import (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smack_sb_kern_mount(struct super_block *sb, int flags, void *data)
{
	struct dentry *root = sb->s_root;
	struct inode *inode = root->d_inode;
	struct superblock_smack *sp = sb->s_security;
	struct inode_smack *isp;
	char *op;
	char *commap;
	char *nsp;

	spin_lock(&sp->smk_sblock);
	if (sp->smk_initialized != 0) {
		spin_unlock(&sp->smk_sblock);
		return 0;
	}
	sp->smk_initialized = 1;
	spin_unlock(&sp->smk_sblock);

	for (op = data; op != NULL; op = commap) {
		commap = strchr(op, ',');
		if (commap != NULL)
			*commap++ = '\0';

		if (strncmp(op, SMK_FSHAT, strlen(SMK_FSHAT)) == 0) {
			op += strlen(SMK_FSHAT);
			nsp = smk_import(op, 0);
			if (nsp != NULL)
				sp->smk_hat = nsp;
		} else if (strncmp(op, SMK_FSFLOOR, strlen(SMK_FSFLOOR)) == 0) {
			op += strlen(SMK_FSFLOOR);
			nsp = smk_import(op, 0);
			if (nsp != NULL)
				sp->smk_floor = nsp;
		} else if (strncmp(op, SMK_FSDEFAULT,
				   strlen(SMK_FSDEFAULT)) == 0) {
			op += strlen(SMK_FSDEFAULT);
			nsp = smk_import(op, 0);
			if (nsp != NULL)
				sp->smk_default = nsp;
		} else if (strncmp(op, SMK_FSROOT, strlen(SMK_FSROOT)) == 0) {
			op += strlen(SMK_FSROOT);
			nsp = smk_import(op, 0);
			if (nsp != NULL)
				sp->smk_root = nsp;
		}
	}

	/*
	 * Initialize the root inode.
	 */
	isp = inode->i_security;
	if (isp == NULL)
		inode->i_security = new_inode_smack(sp->smk_root);
	else
		isp->smk_inode = sp->smk_root;

	return 0;
}