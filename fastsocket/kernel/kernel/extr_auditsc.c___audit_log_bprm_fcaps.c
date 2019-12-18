#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct linux_binprm {TYPE_2__* file; } ;
struct dentry {int dummy; } ;
struct cred {int /*<<< orphan*/  cap_effective; int /*<<< orphan*/  cap_inheritable; int /*<<< orphan*/  cap_permitted; } ;
struct cpu_vfs_cap_data {int magic_etc; int /*<<< orphan*/  inheritable; int /*<<< orphan*/  permitted; } ;
struct audit_context {void* aux; } ;
struct TYPE_11__ {int /*<<< orphan*/  effective; int /*<<< orphan*/  inheritable; int /*<<< orphan*/  permitted; } ;
struct TYPE_10__ {int /*<<< orphan*/  effective; int /*<<< orphan*/  inheritable; int /*<<< orphan*/  permitted; } ;
struct TYPE_9__ {int fE; int /*<<< orphan*/  inheritable; int /*<<< orphan*/  permitted; } ;
struct TYPE_7__ {void* next; int /*<<< orphan*/  type; } ;
struct audit_aux_data_bprm_fcaps {int fcap_ver; TYPE_5__ new_pcap; TYPE_4__ old_pcap; TYPE_3__ fcap; TYPE_1__ d; } ;
struct TYPE_12__ {struct audit_context* audit_context; } ;
struct TYPE_8__ {int /*<<< orphan*/  f_dentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_BPRM_FCAPS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int VFS_CAP_FLAGS_EFFECTIVE ; 
 int VFS_CAP_REVISION_MASK ; 
 int VFS_CAP_REVISION_SHIFT ; 
 TYPE_6__* current ; 
 struct dentry* dget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  get_vfs_caps_from_disk (struct dentry*,struct cpu_vfs_cap_data*) ; 
 struct audit_aux_data_bprm_fcaps* kmalloc (int,int /*<<< orphan*/ ) ; 

int __audit_log_bprm_fcaps(struct linux_binprm *bprm,
			   const struct cred *new, const struct cred *old)
{
	struct audit_aux_data_bprm_fcaps *ax;
	struct audit_context *context = current->audit_context;
	struct cpu_vfs_cap_data vcaps;
	struct dentry *dentry;

	ax = kmalloc(sizeof(*ax), GFP_KERNEL);
	if (!ax)
		return -ENOMEM;

	ax->d.type = AUDIT_BPRM_FCAPS;
	ax->d.next = context->aux;
	context->aux = (void *)ax;

	dentry = dget(bprm->file->f_dentry);
	get_vfs_caps_from_disk(dentry, &vcaps);
	dput(dentry);

	ax->fcap.permitted = vcaps.permitted;
	ax->fcap.inheritable = vcaps.inheritable;
	ax->fcap.fE = !!(vcaps.magic_etc & VFS_CAP_FLAGS_EFFECTIVE);
	ax->fcap_ver = (vcaps.magic_etc & VFS_CAP_REVISION_MASK) >> VFS_CAP_REVISION_SHIFT;

	ax->old_pcap.permitted   = old->cap_permitted;
	ax->old_pcap.inheritable = old->cap_inheritable;
	ax->old_pcap.effective   = old->cap_effective;

	ax->new_pcap.permitted   = new->cap_permitted;
	ax->new_pcap.inheritable = new->cap_inheritable;
	ax->new_pcap.effective   = new->cap_effective;
	return 0;
}