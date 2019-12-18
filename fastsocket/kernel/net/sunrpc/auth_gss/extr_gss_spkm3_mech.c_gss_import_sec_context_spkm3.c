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
typedef  int /*<<< orphan*/  version ;
struct TYPE_2__ {struct spkm3_ctx* data; } ;
struct spkm3_ctx {int endtime; int ret_flags; TYPE_1__ ctx_id; TYPE_1__ mech_used; TYPE_1__ conf_alg; TYPE_1__ derived_conf_key; TYPE_1__ intg_alg; TYPE_1__ derived_integ_key; } ;
struct gss_ctx {struct spkm3_ctx* internal_ctx_id; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  EINVAL ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (void const*) ; 
 int PTR_ERR (void const*) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  kfree (struct spkm3_ctx*) ; 
 struct spkm3_ctx* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* simple_get_bytes (void const*,void const*,int*,int) ; 
 void* simple_get_netobj (void const*,void const*,TYPE_1__*) ; 

__attribute__((used)) static int
gss_import_sec_context_spkm3(const void *p, size_t len,
				struct gss_ctx *ctx_id,
				gfp_t gfp_mask)
{
	const void *end = (const void *)((const char *)p + len);
	struct	spkm3_ctx *ctx;
	int	version;

	if (!(ctx = kzalloc(sizeof(*ctx), gfp_mask)))
		goto out_err;

	p = simple_get_bytes(p, end, &version, sizeof(version));
	if (IS_ERR(p))
		goto out_err_free_ctx;
	if (version != 1) {
		dprintk("RPC:       unknown spkm3 token format: "
				"obsolete nfs-utils?\n");
		p = ERR_PTR(-EINVAL);
		goto out_err_free_ctx;
	}

	p = simple_get_netobj(p, end, &ctx->ctx_id);
	if (IS_ERR(p))
		goto out_err_free_ctx;

	p = simple_get_bytes(p, end, &ctx->endtime, sizeof(ctx->endtime));
	if (IS_ERR(p))
		goto out_err_free_ctx_id;

	p = simple_get_netobj(p, end, &ctx->mech_used);
	if (IS_ERR(p))
		goto out_err_free_ctx_id;

	p = simple_get_bytes(p, end, &ctx->ret_flags, sizeof(ctx->ret_flags));
	if (IS_ERR(p))
		goto out_err_free_mech;

	p = simple_get_netobj(p, end, &ctx->conf_alg);
	if (IS_ERR(p))
		goto out_err_free_mech;

	p = simple_get_netobj(p, end, &ctx->derived_conf_key);
	if (IS_ERR(p))
		goto out_err_free_conf_alg;

	p = simple_get_netobj(p, end, &ctx->intg_alg);
	if (IS_ERR(p))
		goto out_err_free_conf_key;

	p = simple_get_netobj(p, end, &ctx->derived_integ_key);
	if (IS_ERR(p))
		goto out_err_free_intg_alg;

	if (p != end) {
		p = ERR_PTR(-EFAULT);
		goto out_err_free_intg_key;
	}

	ctx_id->internal_ctx_id = ctx;

	dprintk("RPC:       Successfully imported new spkm context.\n");
	return 0;

out_err_free_intg_key:
	kfree(ctx->derived_integ_key.data);
out_err_free_intg_alg:
	kfree(ctx->intg_alg.data);
out_err_free_conf_key:
	kfree(ctx->derived_conf_key.data);
out_err_free_conf_alg:
	kfree(ctx->conf_alg.data);
out_err_free_mech:
	kfree(ctx->mech_used.data);
out_err_free_ctx_id:
	kfree(ctx->ctx_id.data);
out_err_free_ctx:
	kfree(ctx);
out_err:
	return PTR_ERR(p);
}