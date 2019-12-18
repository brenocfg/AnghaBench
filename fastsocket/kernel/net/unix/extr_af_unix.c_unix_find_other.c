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
struct sockaddr_un {scalar_t__* sun_path; } ;
struct sock {int sk_type; } ;
struct path {struct dentry* dentry; int /*<<< orphan*/  mnt; } ;
struct net {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct dentry {struct inode* d_inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  mnt; struct dentry* dentry; } ;

/* Variables and functions */
 int ECONNREFUSED ; 
 int EPROTOTYPE ; 
 int /*<<< orphan*/  LOOKUP_FOLLOW ; 
 int /*<<< orphan*/  MAY_WRITE ; 
 int /*<<< orphan*/  S_ISSOCK (int /*<<< orphan*/ ) ; 
 int inode_permission (struct inode*,int /*<<< orphan*/ ) ; 
 int kern_path (scalar_t__*,int /*<<< orphan*/ ,struct path*) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  touch_atime (int /*<<< orphan*/ ,struct dentry*) ; 
 struct sock* unix_find_socket_byinode (struct inode*) ; 
 struct sock* unix_find_socket_byname (struct net*,struct sockaddr_un*,int,int,unsigned int) ; 
 TYPE_1__* unix_sk (struct sock*) ; 

__attribute__((used)) static struct sock *unix_find_other(struct net *net,
				    struct sockaddr_un *sunname, int len,
				    int type, unsigned hash, int *error)
{
	struct sock *u;
	struct path path;
	int err = 0;

	if (sunname->sun_path[0]) {
		struct inode *inode;
		err = kern_path(sunname->sun_path, LOOKUP_FOLLOW, &path);
		if (err)
			goto fail;
		inode = path.dentry->d_inode;
		err = inode_permission(inode, MAY_WRITE);
		if (err)
			goto put_fail;

		err = -ECONNREFUSED;
		if (!S_ISSOCK(inode->i_mode))
			goto put_fail;
		u = unix_find_socket_byinode(inode);
		if (!u)
			goto put_fail;

		if (u->sk_type == type)
			touch_atime(path.mnt, path.dentry);

		path_put(&path);

		err = -EPROTOTYPE;
		if (u->sk_type != type) {
			sock_put(u);
			goto fail;
		}
	} else {
		err = -ECONNREFUSED;
		u = unix_find_socket_byname(net, sunname, len, type, hash);
		if (u) {
			struct dentry *dentry;
			dentry = unix_sk(u)->dentry;
			if (dentry)
				touch_atime(unix_sk(u)->mnt, dentry);
		} else
			goto fail;
	}
	return u;

put_fail:
	path_put(&path);
fail:
	*error = err;
	return NULL;
}