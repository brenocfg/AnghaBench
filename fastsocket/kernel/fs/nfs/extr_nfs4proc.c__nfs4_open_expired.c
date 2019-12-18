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
struct nfs_open_context {int /*<<< orphan*/  dentry; } ;
struct nfs4_state {int dummy; } ;
struct nfs4_opendata {int dummy; } ;

/* Variables and functions */
 int ESTALE ; 
 scalar_t__ IS_ERR (struct nfs4_opendata*) ; 
 int /*<<< orphan*/  NFS4_OPEN_CLAIM_FH ; 
 int PTR_ERR (struct nfs4_opendata*) ; 
 int /*<<< orphan*/  d_drop (int /*<<< orphan*/ ) ; 
 int nfs4_open_recover (struct nfs4_opendata*,struct nfs4_state*) ; 
 struct nfs4_opendata* nfs4_open_recoverdata_alloc (struct nfs_open_context*,struct nfs4_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_opendata_put (struct nfs4_opendata*) ; 

__attribute__((used)) static int _nfs4_open_expired(struct nfs_open_context *ctx, struct nfs4_state *state)
{
	struct nfs4_opendata *opendata;
	int ret;

	opendata = nfs4_open_recoverdata_alloc(ctx, state,
			NFS4_OPEN_CLAIM_FH);
	if (IS_ERR(opendata))
		return PTR_ERR(opendata);
	ret = nfs4_open_recover(opendata, state);
	if (ret == -ESTALE)
		d_drop(ctx->dentry);
	nfs4_opendata_put(opendata);
	return ret;
}