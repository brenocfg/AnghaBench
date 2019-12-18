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
struct policy_load_memory {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct inode {int /*<<< orphan*/  i_mutex; } ;
struct file {struct policy_load_memory* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (struct policy_load_memory*) ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SECURITY__READ_POLICY ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct policy_load_memory*) ; 
 struct policy_load_memory* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int policy_opened ; 
 scalar_t__ security_policydb_len () ; 
 int security_read_policy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sel_mutex ; 
 int task_has_security (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sel_open_policy(struct inode *inode, struct file *filp)
{
	struct policy_load_memory *plm = NULL;
	int rc;

	BUG_ON(filp->private_data);

	mutex_lock(&sel_mutex);

	rc = task_has_security(current, SECURITY__READ_POLICY);
	if (rc)
		goto err;

	rc = -EBUSY;
	if (policy_opened)
		goto err;

	rc = -ENOMEM;
	plm = kzalloc(sizeof(*plm), GFP_KERNEL);
	if (!plm)
		goto err;

	if (i_size_read(inode) != security_policydb_len()) {
		mutex_lock(&inode->i_mutex);
		i_size_write(inode, security_policydb_len());
		mutex_unlock(&inode->i_mutex);
	}

	rc = security_read_policy(&plm->data, &plm->len);
	if (rc)
		goto err;

	policy_opened = 1;

	filp->private_data = plm;

	mutex_unlock(&sel_mutex);

	return 0;
err:
	mutex_unlock(&sel_mutex);

	if (plm)
		vfree(plm->data);
	kfree(plm);
	return rc;
}