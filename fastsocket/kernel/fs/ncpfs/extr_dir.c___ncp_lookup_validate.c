#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ncp_server {int dummy; } ;
struct TYPE_10__ {scalar_t__ dirEntNum; int /*<<< orphan*/  volNumber; } ;
struct ncp_entry_info {TYPE_4__ i; int /*<<< orphan*/  volume; } ;
struct inode {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dentry {struct inode* d_inode; TYPE_3__* d_parent; TYPE_1__ d_name; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __name ;
struct TYPE_11__ {scalar_t__ dirEntNum; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct TYPE_9__ {TYPE_2__ d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDPRINTK (char*,...) ; 
 TYPE_6__* NCP_FINFO (struct inode*) ; 
 int /*<<< orphan*/  NCP_GET_AGE (struct dentry*) ; 
 int /*<<< orphan*/  NCP_MAXPATHLEN ; 
 struct ncp_server* NCP_SERVER (struct inode*) ; 
 int NCP_TEST_AGE (struct ncp_server*,struct dentry*) ; 
 struct dentry* dget_parent (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  ncp_conn_valid (struct ncp_server*) ; 
 int ncp_io2vol (struct ncp_server*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ncp_is_server_root (struct inode*) ; 
 int ncp_lookup_volume (struct ncp_server*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  ncp_new_dentry (struct dentry*) ; 
 int ncp_obtain_info (struct ncp_server*,struct inode*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  ncp_preserve_case (struct inode*) ; 
 int /*<<< orphan*/  ncp_update_inode2 (struct inode*,struct ncp_entry_info*) ; 

__attribute__((used)) static int
__ncp_lookup_validate(struct dentry *dentry)
{
	struct ncp_server *server;
	struct dentry *parent;
	struct inode *dir;
	struct ncp_entry_info finfo;
	int res, val = 0, len;
	__u8 __name[NCP_MAXPATHLEN + 1];

	parent = dget_parent(dentry);
	dir = parent->d_inode;

	if (!dentry->d_inode)
		goto finished;

	server = NCP_SERVER(dir);

	if (!ncp_conn_valid(server))
		goto finished;

	/*
	 * Inspired by smbfs:
	 * The default validation is based on dentry age:
	 * We set the max age at mount time.  (But each
	 * successful server lookup renews the timestamp.)
	 */
	val = NCP_TEST_AGE(server, dentry);
	if (val)
		goto finished;

	DDPRINTK("ncp_lookup_validate: %s/%s not valid, age=%ld, server lookup\n",
		dentry->d_parent->d_name.name, dentry->d_name.name,
		NCP_GET_AGE(dentry));

	len = sizeof(__name);
	if (ncp_is_server_root(dir)) {
		res = ncp_io2vol(server, __name, &len, dentry->d_name.name,
				 dentry->d_name.len, 1);
		if (!res)
			res = ncp_lookup_volume(server, __name, &(finfo.i));
	} else {
		res = ncp_io2vol(server, __name, &len, dentry->d_name.name,
				 dentry->d_name.len, !ncp_preserve_case(dir));
		if (!res)
			res = ncp_obtain_info(server, dir, __name, &(finfo.i));
	}
	finfo.volume = finfo.i.volNumber;
	DDPRINTK("ncp_lookup_validate: looked for %s/%s, res=%d\n",
		dentry->d_parent->d_name.name, __name, res);
	/*
	 * If we didn't find it, or if it has a different dirEntNum to
	 * what we remember, it's not valid any more.
	 */
	if (!res) {
		if (finfo.i.dirEntNum == NCP_FINFO(dentry->d_inode)->dirEntNum) {
			ncp_new_dentry(dentry);
			val=1;
		} else
			DDPRINTK("ncp_lookup_validate: found, but dirEntNum changed\n");

		ncp_update_inode2(dentry->d_inode, &finfo);
	}

finished:
	DDPRINTK("ncp_lookup_validate: result=%d\n", val);
	dput(parent);
	return val;
}