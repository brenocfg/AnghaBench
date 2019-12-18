#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct superblock_security_struct {int flags; TYPE_2__* sb; int /*<<< orphan*/  def_sid; int /*<<< orphan*/  mntpoint_sid; int /*<<< orphan*/  sid; } ;
struct super_block {struct superblock_security_struct* s_security; } ;
struct security_mnt_opts {int num_mnt_opts; char** mnt_opts; int* mnt_opts_flags; } ;
struct inode_security_struct {int /*<<< orphan*/  sid; } ;
struct inode {struct inode_security_struct* i_security; } ;
struct TYPE_4__ {TYPE_1__* s_root; } ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CONTEXT_MNT ; 
 int DEFCONTEXT_MNT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int FSCONTEXT_MNT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int ROOTCONTEXT_MNT ; 
 char SE_MNTMASK ; 
 int SE_SBINITIALIZED ; 
 int SE_SBLABELSUPP ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  security_free_mnt_opts (struct security_mnt_opts*) ; 
 int /*<<< orphan*/  security_init_mnt_opts (struct security_mnt_opts*) ; 
 int security_sid_to_context (int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ss_initialized ; 

__attribute__((used)) static int selinux_get_mnt_opts(const struct super_block *sb,
				struct security_mnt_opts *opts)
{
	int rc = 0, i;
	struct superblock_security_struct *sbsec = sb->s_security;
	char *context = NULL;
	u32 len;
	char tmp;

	security_init_mnt_opts(opts);

	if (!(sbsec->flags & SE_SBINITIALIZED))
		return -EINVAL;

	if (!ss_initialized)
		return -EINVAL;

	tmp = sbsec->flags & SE_MNTMASK;
	/* count the number of mount options for this sb */
	for (i = 0; i < 8; i++) {
		if (tmp & 0x01)
			opts->num_mnt_opts++;
		tmp >>= 1;
	}
	/* Check if the Label support flag is set */
	if (sbsec->flags & SE_SBLABELSUPP)
		opts->num_mnt_opts++;

	opts->mnt_opts = kcalloc(opts->num_mnt_opts, sizeof(char *), GFP_ATOMIC);
	if (!opts->mnt_opts) {
		rc = -ENOMEM;
		goto out_free;
	}

	opts->mnt_opts_flags = kcalloc(opts->num_mnt_opts, sizeof(int), GFP_ATOMIC);
	if (!opts->mnt_opts_flags) {
		rc = -ENOMEM;
		goto out_free;
	}

	i = 0;
	if (sbsec->flags & FSCONTEXT_MNT) {
		rc = security_sid_to_context(sbsec->sid, &context, &len);
		if (rc)
			goto out_free;
		opts->mnt_opts[i] = context;
		opts->mnt_opts_flags[i++] = FSCONTEXT_MNT;
	}
	if (sbsec->flags & CONTEXT_MNT) {
		rc = security_sid_to_context(sbsec->mntpoint_sid, &context, &len);
		if (rc)
			goto out_free;
		opts->mnt_opts[i] = context;
		opts->mnt_opts_flags[i++] = CONTEXT_MNT;
	}
	if (sbsec->flags & DEFCONTEXT_MNT) {
		rc = security_sid_to_context(sbsec->def_sid, &context, &len);
		if (rc)
			goto out_free;
		opts->mnt_opts[i] = context;
		opts->mnt_opts_flags[i++] = DEFCONTEXT_MNT;
	}
	if (sbsec->flags & ROOTCONTEXT_MNT) {
		struct inode *root = sbsec->sb->s_root->d_inode;
		struct inode_security_struct *isec = root->i_security;

		rc = security_sid_to_context(isec->sid, &context, &len);
		if (rc)
			goto out_free;
		opts->mnt_opts[i] = context;
		opts->mnt_opts_flags[i++] = ROOTCONTEXT_MNT;
	}
	if (sbsec->flags & SE_SBLABELSUPP) {
		opts->mnt_opts[i] = NULL;
		opts->mnt_opts_flags[i++] = SE_SBLABELSUPP;
	}

	BUG_ON(i != opts->num_mnt_opts);

	return 0;

out_free:
	security_free_mnt_opts(opts);
	return rc;
}