#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct nfs_server {int /*<<< orphan*/  attr_bitmask; TYPE_1__* nfs_client; } ;
struct TYPE_10__ {int /*<<< orphan*/  id; } ;
struct nfs4_state_owner {TYPE_2__ so_owner_id; int /*<<< orphan*/  so_count; int /*<<< orphan*/  so_seqid; } ;
struct TYPE_11__ {scalar_t__ data; } ;
struct TYPE_12__ {TYPE_3__ verifier; int /*<<< orphan*/ * attrs; } ;
struct TYPE_15__ {int open_flags; int fmode; int access; int claim; int /*<<< orphan*/ * seqid; TYPE_4__ u; void* fh; int /*<<< orphan*/  bitmask; struct nfs_server* server; int /*<<< orphan*/ * name; int /*<<< orphan*/  id; int /*<<< orphan*/  clientid; } ;
struct TYPE_14__ {int /*<<< orphan*/ * seqid; int /*<<< orphan*/ * stateid; int /*<<< orphan*/ * fh; } ;
struct TYPE_13__ {int /*<<< orphan*/  stateid; int /*<<< orphan*/  fh; } ;
struct nfs4_opendata {int /*<<< orphan*/  kref; TYPE_7__ o_arg; TYPE_6__ c_arg; TYPE_5__ o_res; int /*<<< orphan*/  attrs; struct nfs4_state_owner* owner; struct dentry* dir; int /*<<< orphan*/  dentry; } ;
struct inode {int dummy; } ;
struct iattr {scalar_t__ ia_valid; } ;
struct dentry {struct inode* d_inode; int /*<<< orphan*/  d_name; int /*<<< orphan*/  d_sb; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int fmode_t ;
typedef  enum open_claim_type4 { ____Placeholder_open_claim_type4 } open_claim_type4 ;
struct TYPE_16__ {int /*<<< orphan*/  pid; } ;
struct TYPE_9__ {int /*<<< orphan*/  cl_clientid; } ;

/* Variables and functions */
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int NFS4_ACCESS_EXECUTE ; 
 int NFS4_ACCESS_EXTEND ; 
 int NFS4_ACCESS_MODIFY ; 
 int NFS4_ACCESS_READ ; 
#define  NFS4_OPEN_CLAIM_DELEGATE_CUR 134 
#define  NFS4_OPEN_CLAIM_DELEGATE_PREV 133 
#define  NFS4_OPEN_CLAIM_DELEG_CUR_FH 132 
#define  NFS4_OPEN_CLAIM_DELEG_PREV_FH 131 
#define  NFS4_OPEN_CLAIM_FH 130 
#define  NFS4_OPEN_CLAIM_NULL 129 
#define  NFS4_OPEN_CLAIM_PREVIOUS 128 
 void* NFS_FH (struct inode*) ; 
 struct nfs_server* NFS_SERVER (struct inode*) ; 
 int O_EXCL ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 TYPE_8__* current ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 struct dentry* dget_parent (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree (struct nfs4_opendata*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct nfs4_opendata* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct iattr const*,int) ; 
 int /*<<< orphan*/  nfs4_init_opendata_res (struct nfs4_opendata*) ; 
 int nfs4_map_atomic_open_claim (struct nfs_server*,int) ; 
 int /*<<< orphan*/ * nfs_alloc_seqid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_sb_active (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nfs4_opendata *nfs4_opendata_alloc(struct dentry *dentry,
		struct nfs4_state_owner *sp, fmode_t fmode, int flags,
		const struct iattr *attrs,
		enum open_claim_type4 claim,
		gfp_t gfp_mask)
{
	struct dentry *parent = dget_parent(dentry);
	struct inode *dir = parent->d_inode;
	struct nfs_server *server = NFS_SERVER(dir);
	struct nfs4_opendata *p;

	p = kzalloc(sizeof(*p), gfp_mask);
	if (p == NULL)
		goto err;
	p->o_arg.seqid = nfs_alloc_seqid(&sp->so_seqid, gfp_mask);
	if (p->o_arg.seqid == NULL)
		goto err_free;
	nfs_sb_active(dentry->d_sb);
	p->dentry = dget(dentry);
	p->dir = parent;
	p->owner = sp;
	atomic_inc(&sp->so_count);
	p->o_arg.open_flags = flags;
	p->o_arg.fmode = fmode & (FMODE_READ|FMODE_WRITE);
	/* don't put an ACCESS op in OPEN compound if O_EXCL, because ACCESS
	 * will return permission denied for all bits until close */
	if (!(flags & O_EXCL)) {
		/* ask server to check for all possible rights as results
		 * are cached */
		p->o_arg.access = NFS4_ACCESS_READ | NFS4_ACCESS_MODIFY |
				  NFS4_ACCESS_EXTEND | NFS4_ACCESS_EXECUTE;
	}
	p->o_arg.clientid = server->nfs_client->cl_clientid;
	p->o_arg.id = sp->so_owner_id.id;
	p->o_arg.name = &dentry->d_name;
	p->o_arg.server = server;
	p->o_arg.bitmask = server->attr_bitmask;
	p->o_arg.claim = nfs4_map_atomic_open_claim(server, claim);
	switch (p->o_arg.claim) {
	case NFS4_OPEN_CLAIM_NULL:
	case NFS4_OPEN_CLAIM_DELEGATE_CUR:
	case NFS4_OPEN_CLAIM_DELEGATE_PREV:
		p->o_arg.fh = NFS_FH(dir);
		break;
	case NFS4_OPEN_CLAIM_PREVIOUS:
	case NFS4_OPEN_CLAIM_FH:
	case NFS4_OPEN_CLAIM_DELEG_CUR_FH:
	case NFS4_OPEN_CLAIM_DELEG_PREV_FH:
		p->o_arg.fh = NFS_FH(dentry->d_inode);
	}
	if (attrs != NULL && attrs->ia_valid != 0) {
		u32 *s;

		p->o_arg.u.attrs = &p->attrs;
		memcpy(&p->attrs, attrs, sizeof(p->attrs));
		s = (u32 *) p->o_arg.u.verifier.data;
		s[0] = jiffies;
		s[1] = current->pid;
	}
	p->c_arg.fh = &p->o_res.fh;
	p->c_arg.stateid = &p->o_res.stateid;
	p->c_arg.seqid = p->o_arg.seqid;
	nfs4_init_opendata_res(p);
	kref_init(&p->kref);
	return p;
err_free:
	kfree(p);
err:
	dput(parent);
	return NULL;
}