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
struct policy_file {unsigned long len; void* data; } ;
typedef  unsigned long ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  policy_rwlock ; 
 int /*<<< orphan*/  policydb ; 
 int policydb_write (int /*<<< orphan*/ *,struct policy_file*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 unsigned long security_policydb_len () ; 
 int /*<<< orphan*/  ss_initialized ; 
 void* vmalloc_user (unsigned long) ; 

int security_read_policy(void **data, ssize_t *len)
{
	int rc;
	struct policy_file fp;

	if (!ss_initialized)
		return -EINVAL;

	*len = security_policydb_len();

	*data = vmalloc_user(*len);
	if (!*data)
		return -ENOMEM;

	fp.data = *data;
	fp.len = *len;

	read_lock(&policy_rwlock);
	rc = policydb_write(&policydb, &fp);
	read_unlock(&policy_rwlock);

	if (rc)
		return rc;

	*len = (unsigned long)fp.data - (unsigned long)*data;
	return 0;

}