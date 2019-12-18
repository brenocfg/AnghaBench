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
struct pid_namespace {struct bsd_acct_struct* bacct; } ;
struct bsd_acct_struct {int /*<<< orphan*/ * file; } ;

/* Variables and functions */
 int /*<<< orphan*/  acct_file_reopen (struct bsd_acct_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acct_lock ; 
 int /*<<< orphan*/  kfree (struct bsd_acct_struct*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void acct_exit_ns(struct pid_namespace *ns)
{
	struct bsd_acct_struct *acct;

	spin_lock(&acct_lock);
	acct = ns->bacct;
	if (acct != NULL) {
		if (acct->file != NULL)
			acct_file_reopen(acct, NULL, NULL);

		kfree(acct);
	}
	spin_unlock(&acct_lock);
}