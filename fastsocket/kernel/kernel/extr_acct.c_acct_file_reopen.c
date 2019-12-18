#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pid_namespace {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  mnt; } ;
struct file {TYPE_1__ f_path; } ;
struct TYPE_6__ {scalar_t__ expires; } ;
struct bsd_acct_struct {int active; TYPE_2__ timer; int /*<<< orphan*/  list; scalar_t__ needcheck; struct pid_namespace* ns; struct file* file; } ;

/* Variables and functions */
 int ACCT_TIMEOUT ; 
 int HZ ; 
 int /*<<< orphan*/  acct_list ; 
 int /*<<< orphan*/  acct_lock ; 
 int /*<<< orphan*/  acct_timeout ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  del_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  do_acct_process (struct bsd_acct_struct*,struct pid_namespace*,struct file*) ; 
 int /*<<< orphan*/  filp_close (struct file*,int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mnt_unpin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_timer (TYPE_2__*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void acct_file_reopen(struct bsd_acct_struct *acct, struct file *file,
		struct pid_namespace *ns)
{
	struct file *old_acct = NULL;
	struct pid_namespace *old_ns = NULL;

	if (acct->file) {
		old_acct = acct->file;
		old_ns = acct->ns;
		del_timer(&acct->timer);
		acct->active = 0;
		acct->needcheck = 0;
		acct->file = NULL;
		acct->ns = NULL;
		list_del(&acct->list);
	}
	if (file) {
		acct->file = file;
		acct->ns = ns;
		acct->needcheck = 0;
		acct->active = 1;
		list_add(&acct->list, &acct_list);
		/* It's been deleted if it was used before so this is safe */
		setup_timer(&acct->timer, acct_timeout, (unsigned long)acct);
		acct->timer.expires = jiffies + ACCT_TIMEOUT*HZ;
		add_timer(&acct->timer);
	}
	if (old_acct) {
		mnt_unpin(old_acct->f_path.mnt);
		spin_unlock(&acct_lock);
		do_acct_process(acct, old_ns, old_acct);
		filp_close(old_acct, NULL);
		spin_lock(&acct_lock);
	}
}