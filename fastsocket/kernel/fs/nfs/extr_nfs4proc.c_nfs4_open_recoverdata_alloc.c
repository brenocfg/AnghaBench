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
struct nfs4_state {int /*<<< orphan*/  count; int /*<<< orphan*/  owner; } ;
struct nfs4_opendata {struct nfs4_state* state; } ;
typedef  enum open_claim_type4 { ____Placeholder_open_claim_type4 } open_claim_type4 ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct nfs4_opendata* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct nfs4_opendata* nfs4_opendata_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nfs4_opendata *nfs4_open_recoverdata_alloc(struct nfs_open_context *ctx,
		struct nfs4_state *state, enum open_claim_type4 claim)
{
	struct nfs4_opendata *opendata;

	opendata = nfs4_opendata_alloc(ctx->dentry, state->owner, 0, 0,
			NULL, claim, GFP_NOFS);
	if (opendata == NULL)
		return ERR_PTR(-ENOMEM);
	opendata->state = state;
	atomic_inc(&state->count);
	return opendata;
}