#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct qstr {int /*<<< orphan*/  len; int /*<<< orphan*/  name; int /*<<< orphan*/  hash; } ;
struct dentry {TYPE_1__* d_op; } ;
struct TYPE_2__ {scalar_t__ (* d_hash ) (struct dentry*,struct qstr*) ;} ;

/* Variables and functions */
 struct dentry* d_lookup (struct dentry*,struct qstr*) ; 
 int /*<<< orphan*/  full_name_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct dentry*,struct qstr*) ; 

struct dentry *d_hash_and_lookup(struct dentry *dir, struct qstr *name)
{
	struct dentry *dentry = NULL;

	/*
	 * Check for a fs-specific hash function. Note that we must
	 * calculate the standard hash first, as the d_op->d_hash()
	 * routine may choose to leave the hash value unchanged.
	 */
	name->hash = full_name_hash(name->name, name->len);
	if (dir->d_op && dir->d_op->d_hash) {
		if (dir->d_op->d_hash(dir, name) < 0)
			goto out;
	}
	dentry = d_lookup(dir, name);
out:
	return dentry;
}