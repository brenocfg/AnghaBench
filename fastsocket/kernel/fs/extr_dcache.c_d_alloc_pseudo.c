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
struct super_block {int dummy; } ;
struct qstr {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_flags; struct dentry* d_parent; struct super_block* d_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCACHE_DISCONNECTED ; 
 struct dentry* d_alloc (int /*<<< orphan*/ *,struct qstr const*) ; 

struct dentry *d_alloc_pseudo(struct super_block *sb, const struct qstr *name)
{
	struct dentry *dentry = d_alloc(NULL, name);
	if (dentry) {
		dentry->d_sb = sb;
		dentry->d_parent = dentry;
		dentry->d_flags |= DCACHE_DISCONNECTED;
	}
	return dentry;
}