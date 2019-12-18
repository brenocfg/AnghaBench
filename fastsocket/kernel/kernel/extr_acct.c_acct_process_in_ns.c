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
struct file {int dummy; } ;
struct bsd_acct_struct {struct file* file; } ;

/* Variables and functions */
 int /*<<< orphan*/  acct_lock ; 
 int /*<<< orphan*/  do_acct_process (struct bsd_acct_struct*,struct pid_namespace*,struct file*) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 int /*<<< orphan*/  get_file (struct file*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void acct_process_in_ns(struct pid_namespace *ns)
{
	struct file *file = NULL;
	struct bsd_acct_struct *acct;

	acct = ns->bacct;
	/*
	 * accelerate the common fastpath:
	 */
	if (!acct || !acct->file)
		return;

	spin_lock(&acct_lock);
	file = acct->file;
	if (unlikely(!file)) {
		spin_unlock(&acct_lock);
		return;
	}
	get_file(file);
	spin_unlock(&acct_lock);

	do_acct_process(acct, ns, file);
	fput(file);
}