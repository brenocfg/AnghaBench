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
struct qstr {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 struct dentry* ERR_PTR (int) ; 
 struct dentry* __lookup_hash (struct qstr*,struct dentry*,int /*<<< orphan*/ *) ; 
 int __lookup_one_len (char const*,struct qstr*,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

struct dentry *lookup_one_noperm(const char *name, struct dentry *base)
{
	int err;
	struct qstr this;

	err = __lookup_one_len(name, &this, base, strlen(name));
	if (err)
		return ERR_PTR(err);
	return __lookup_hash(&this, base, NULL);
}