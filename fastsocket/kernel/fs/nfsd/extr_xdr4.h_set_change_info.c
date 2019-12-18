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
struct TYPE_7__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_8__ {TYPE_3__ ctime; } ;
struct TYPE_6__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct svc_fh {TYPE_4__ fh_post_attr; TYPE_2__ fh_pre_ctime; int /*<<< orphan*/  fh_post_change; int /*<<< orphan*/  fh_pre_change; TYPE_1__* fh_dentry; int /*<<< orphan*/  fh_post_saved; int /*<<< orphan*/  fh_pre_saved; } ;
struct nfsd4_change_info {int /*<<< orphan*/  after_ctime_nsec; int /*<<< orphan*/  after_ctime_sec; int /*<<< orphan*/  before_ctime_nsec; int /*<<< orphan*/  before_ctime_sec; int /*<<< orphan*/  after_change; int /*<<< orphan*/  before_change; int /*<<< orphan*/  change_supported; int /*<<< orphan*/  atomic; } ;
struct TYPE_5__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  IS_I_VERSION (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
set_change_info(struct nfsd4_change_info *cinfo, struct svc_fh *fhp)
{
	BUG_ON(!fhp->fh_pre_saved);
	cinfo->atomic = fhp->fh_post_saved;
	cinfo->change_supported = IS_I_VERSION(fhp->fh_dentry->d_inode);

	cinfo->before_change = fhp->fh_pre_change;
	cinfo->after_change = fhp->fh_post_change;
	cinfo->before_ctime_sec = fhp->fh_pre_ctime.tv_sec;
	cinfo->before_ctime_nsec = fhp->fh_pre_ctime.tv_nsec;
	cinfo->after_ctime_sec = fhp->fh_post_attr.ctime.tv_sec;
	cinfo->after_ctime_nsec = fhp->fh_post_attr.ctime.tv_nsec;

}