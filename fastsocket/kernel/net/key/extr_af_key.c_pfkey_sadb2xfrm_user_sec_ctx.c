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
struct xfrm_user_sec_ctx {int ctx_len; int /*<<< orphan*/  ctx_alg; int /*<<< orphan*/  ctx_doi; int /*<<< orphan*/  exttype; int /*<<< orphan*/  len; } ;
struct sadb_x_sec_ctx {int sadb_x_ctx_len; int /*<<< orphan*/  sadb_x_ctx_alg; int /*<<< orphan*/  sadb_x_ctx_doi; int /*<<< orphan*/  sadb_x_sec_exttype; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct xfrm_user_sec_ctx* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct xfrm_user_sec_ctx*,struct sadb_x_sec_ctx*,int) ; 
 int /*<<< orphan*/  pfkey_sec_ctx_len (struct sadb_x_sec_ctx*) ; 

__attribute__((used)) static inline struct xfrm_user_sec_ctx *pfkey_sadb2xfrm_user_sec_ctx(struct sadb_x_sec_ctx *sec_ctx)
{
	struct xfrm_user_sec_ctx *uctx = NULL;
	int ctx_size = sec_ctx->sadb_x_ctx_len;

	uctx = kmalloc((sizeof(*uctx)+ctx_size), GFP_KERNEL);

	if (!uctx)
		return NULL;

	uctx->len = pfkey_sec_ctx_len(sec_ctx);
	uctx->exttype = sec_ctx->sadb_x_sec_exttype;
	uctx->ctx_doi = sec_ctx->sadb_x_ctx_doi;
	uctx->ctx_alg = sec_ctx->sadb_x_ctx_alg;
	uctx->ctx_len = sec_ctx->sadb_x_ctx_len;
	memcpy(uctx + 1, sec_ctx + 1,
	       uctx->ctx_len);

	return uctx;
}