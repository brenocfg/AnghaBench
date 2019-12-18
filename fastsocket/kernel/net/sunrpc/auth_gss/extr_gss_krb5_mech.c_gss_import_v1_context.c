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
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct krb5_ctx {int initiate; int endtime; int seq_send; TYPE_1__ mech_used; int /*<<< orphan*/  enc; int /*<<< orphan*/  seq; int /*<<< orphan*/ * gk5e; int /*<<< orphan*/  enctype; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENCTYPE_DES_CBC_RAW ; 
 int /*<<< orphan*/  ENOSYS ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (void const*) ; 
 int PTR_ERR (void const*) ; 
 int SEAL_ALG_DES ; 
 int SGN_ALG_DES_MAC_MD5 ; 
 int /*<<< orphan*/  crypto_free_blkcipher (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_gss_krb5_enctype (int /*<<< orphan*/ ) ; 
 void* get_key (void const*,void const*,struct krb5_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 void* simple_get_bytes (void const*,void const*,int*,int) ; 
 void* simple_get_netobj (void const*,void const*,TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
gss_import_v1_context(const void *p, const void *end, struct krb5_ctx *ctx)
{
	int tmp;

	p = simple_get_bytes(p, end, &ctx->initiate, sizeof(ctx->initiate));
	if (IS_ERR(p))
		goto out_err;

	/* Old format supports only DES!  Any other enctype uses new format */
	ctx->enctype = ENCTYPE_DES_CBC_RAW;

	ctx->gk5e = get_gss_krb5_enctype(ctx->enctype);
	if (ctx->gk5e == NULL) {
		p = ERR_PTR(-EINVAL);
		goto out_err;
	}

	/* The downcall format was designed before we completely understood
	 * the uses of the context fields; so it includes some stuff we
	 * just give some minimal sanity-checking, and some we ignore
	 * completely (like the next twenty bytes): */
	if (unlikely(p + 20 > end || p + 20 < p)) {
		p = ERR_PTR(-EFAULT);
		goto out_err;
	}
	p += 20;
	p = simple_get_bytes(p, end, &tmp, sizeof(tmp));
	if (IS_ERR(p))
		goto out_err;
	if (tmp != SGN_ALG_DES_MAC_MD5) {
		p = ERR_PTR(-ENOSYS);
		goto out_err;
	}
	p = simple_get_bytes(p, end, &tmp, sizeof(tmp));
	if (IS_ERR(p))
		goto out_err;
	if (tmp != SEAL_ALG_DES) {
		p = ERR_PTR(-ENOSYS);
		goto out_err;
	}
	p = simple_get_bytes(p, end, &ctx->endtime, sizeof(ctx->endtime));
	if (IS_ERR(p))
		goto out_err;
	p = simple_get_bytes(p, end, &ctx->seq_send, sizeof(ctx->seq_send));
	if (IS_ERR(p))
		goto out_err;
	p = simple_get_netobj(p, end, &ctx->mech_used);
	if (IS_ERR(p))
		goto out_err;
	p = get_key(p, end, ctx, &ctx->enc);
	if (IS_ERR(p))
		goto out_err_free_mech;
	p = get_key(p, end, ctx, &ctx->seq);
	if (IS_ERR(p))
		goto out_err_free_key1;
	if (p != end) {
		p = ERR_PTR(-EFAULT);
		goto out_err_free_key2;
	}

	return 0;

out_err_free_key2:
	crypto_free_blkcipher(ctx->seq);
out_err_free_key1:
	crypto_free_blkcipher(ctx->enc);
out_err_free_mech:
	kfree(ctx->mech_used.data);
out_err:
	return PTR_ERR(p);
}