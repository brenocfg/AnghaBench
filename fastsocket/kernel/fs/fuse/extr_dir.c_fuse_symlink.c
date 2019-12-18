#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  opcode; } ;
struct TYPE_8__ {int numargs; TYPE_3__* args; TYPE_1__ h; } ;
struct fuse_req {TYPE_4__ in; } ;
struct fuse_conn {int dummy; } ;
struct TYPE_6__ {int len; char const* name; } ;
struct dentry {TYPE_2__ d_name; } ;
struct TYPE_7__ {int size; char const* value; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_SYMLINK ; 
 scalar_t__ IS_ERR (struct fuse_req*) ; 
 int PTR_ERR (struct fuse_req*) ; 
 int /*<<< orphan*/  S_IFLNK ; 
 int create_new_entry (struct fuse_conn*,struct fuse_req*,struct inode*,struct dentry*,int /*<<< orphan*/ ) ; 
 struct fuse_req* fuse_get_req_nopages (struct fuse_conn*) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int fuse_symlink(struct inode *dir, struct dentry *entry,
			const char *link)
{
	struct fuse_conn *fc = get_fuse_conn(dir);
	unsigned len = strlen(link) + 1;
	struct fuse_req *req = fuse_get_req_nopages(fc);
	if (IS_ERR(req))
		return PTR_ERR(req);

	req->in.h.opcode = FUSE_SYMLINK;
	req->in.numargs = 2;
	req->in.args[0].size = entry->d_name.len + 1;
	req->in.args[0].value = entry->d_name.name;
	req->in.args[1].size = len;
	req->in.args[1].value = link;
	return create_new_entry(fc, req, dir, entry, S_IFLNK);
}