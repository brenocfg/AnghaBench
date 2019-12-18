#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct superblock_security_struct {int flags; int /*<<< orphan*/  sid; } ;
struct inode_security_struct {int /*<<< orphan*/  sclass; int /*<<< orphan*/  sid; } ;
struct inode {TYPE_1__* i_sb; struct inode_security_struct* i_security; } ;
struct dentry {struct inode* d_inode; } ;
struct TYPE_6__ {struct dentry* dentry; } ;
struct TYPE_7__ {TYPE_2__ path; } ;
struct TYPE_8__ {TYPE_3__ fs; } ;
struct common_audit_data {TYPE_4__ u; } ;
struct TYPE_5__ {struct superblock_security_struct* s_security; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_MAC_ADMIN ; 
 int /*<<< orphan*/  COMMON_AUDIT_DATA_INIT (struct common_audit_data*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 int /*<<< orphan*/  FILESYSTEM__ASSOCIATE ; 
 int /*<<< orphan*/  FILE__RELABELFROM ; 
 int /*<<< orphan*/  FILE__RELABELTO ; 
 int /*<<< orphan*/  FS ; 
 int /*<<< orphan*/  SECCLASS_FILESYSTEM ; 
 int SE_SBLABELSUPP ; 
 int /*<<< orphan*/  XATTR_NAME_SELINUX ; 
 int avc_has_perm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct common_audit_data*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_sid () ; 
 int /*<<< orphan*/  is_owner_or_cap (struct inode*) ; 
 int security_context_to_sid (void const*,size_t,int /*<<< orphan*/ *) ; 
 int security_context_to_sid_force (void const*,size_t,int /*<<< orphan*/ *) ; 
 int security_validate_transition (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int selinux_inode_setotherxattr (struct dentry*,char const*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int selinux_inode_setxattr(struct dentry *dentry, const char *name,
				  const void *value, size_t size, int flags)
{
	struct inode *inode = dentry->d_inode;
	struct inode_security_struct *isec = inode->i_security;
	struct superblock_security_struct *sbsec;
	struct common_audit_data ad;
	u32 newsid, sid = current_sid();
	int rc = 0;

	if (strcmp(name, XATTR_NAME_SELINUX))
		return selinux_inode_setotherxattr(dentry, name);

	sbsec = inode->i_sb->s_security;
	if (!(sbsec->flags & SE_SBLABELSUPP))
		return -EOPNOTSUPP;

	if (!is_owner_or_cap(inode))
		return -EPERM;

	COMMON_AUDIT_DATA_INIT(&ad, FS);
	ad.u.fs.path.dentry = dentry;

	rc = avc_has_perm(sid, isec->sid, isec->sclass,
			  FILE__RELABELFROM, &ad);
	if (rc)
		return rc;

	rc = security_context_to_sid(value, size, &newsid);
	if (rc == -EINVAL) {
		if (!capable(CAP_MAC_ADMIN))
			return rc;
		rc = security_context_to_sid_force(value, size, &newsid);
	}
	if (rc)
		return rc;

	rc = avc_has_perm(sid, newsid, isec->sclass,
			  FILE__RELABELTO, &ad);
	if (rc)
		return rc;

	rc = security_validate_transition(isec->sid, newsid, sid,
					  isec->sclass);
	if (rc)
		return rc;

	return avc_has_perm(newsid,
			    sbsec->sid,
			    SECCLASS_FILESYSTEM,
			    FILESYSTEM__ASSOCIATE,
			    &ad);
}