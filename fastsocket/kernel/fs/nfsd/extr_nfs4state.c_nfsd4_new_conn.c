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
typedef  int /*<<< orphan*/  u32 ;
struct svc_rqst {int dummy; } ;
struct nfsd4_session {int se_flags; } ;
struct nfsd4_conn {int /*<<< orphan*/  cn_xpt_user; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4_CDFC4_BACK ; 
 int /*<<< orphan*/  NFS4_CDFC4_FORE ; 
 int SESSION4_BACK_CHAN ; 
 struct nfsd4_conn* alloc_conn (struct svc_rqst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_ok ; 
 int /*<<< orphan*/  nfsd4_conn_lost (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd4_hash_conn (struct nfsd4_conn*,struct nfsd4_session*) ; 
 int nfsd4_register_conn (struct nfsd4_conn*) ; 
 int /*<<< orphan*/  nfserr_jukebox ; 

__attribute__((used)) static __be32 nfsd4_new_conn(struct svc_rqst *rqstp, struct nfsd4_session *ses)
{
	struct nfsd4_conn *conn;
	u32 flags = NFS4_CDFC4_FORE;
	int ret;

	if (ses->se_flags & SESSION4_BACK_CHAN)
		flags |= NFS4_CDFC4_BACK;
	conn = alloc_conn(rqstp, flags);
	if (!conn)
		return nfserr_jukebox;
	nfsd4_hash_conn(conn, ses);
	ret = nfsd4_register_conn(conn);
	if (ret)
		/* oops; xprt is already down: */
		nfsd4_conn_lost(&conn->cn_xpt_user);
	return nfs_ok;
}