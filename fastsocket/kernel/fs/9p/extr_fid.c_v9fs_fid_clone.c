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
struct p9_fid {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct p9_fid*) ; 
 struct p9_fid* p9_client_walk (struct p9_fid*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct p9_fid* v9fs_fid_lookup (struct dentry*) ; 

struct p9_fid *v9fs_fid_clone(struct dentry *dentry)
{
	struct p9_fid *fid, *ret;

	fid = v9fs_fid_lookup(dentry);
	if (IS_ERR(fid))
		return fid;

	ret = p9_client_walk(fid, 0, NULL, 1);
	return ret;
}