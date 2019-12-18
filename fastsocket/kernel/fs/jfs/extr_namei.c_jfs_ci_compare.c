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
struct qstr {int len; int /*<<< orphan*/ * name; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ tolower (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jfs_ci_compare(struct dentry *dir, struct qstr *a, struct qstr *b)
{
	int i, result = 1;

	if (a->len != b->len)
		goto out;
	for (i=0; i < a->len; i++) {
		if (tolower(a->name[i]) != tolower(b->name[i]))
			goto out;
	}
	result = 0;

	/*
	 * We want creates to preserve case.  A negative dentry, a, that
	 * has a different case than b may cause a new entry to be created
	 * with the wrong case.  Since we can't tell if a comes from a negative
	 * dentry, we blindly replace it with b.  This should be harmless if
	 * a is not a negative dentry.
	 */
	memcpy((unsigned char *)a->name, b->name, a->len);
out:
	return result;
}