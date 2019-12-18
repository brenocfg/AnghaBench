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
typedef  int /*<<< orphan*/  window_size ;
typedef  unsigned int u32 ;
typedef  int /*<<< orphan*/  timeout ;
struct gss_cl_ctx {unsigned int gc_win; int /*<<< orphan*/  gc_gss_ctx; int /*<<< orphan*/  gc_wire_ctx; scalar_t__ gc_expiry; } ;
struct gss_api_mech {int dummy; } ;
typedef  int /*<<< orphan*/  seclen ;
typedef  int /*<<< orphan*/  ret ;

/* Variables and functions */
 int EACCES ; 
 int EFAULT ; 
 int EKEYEXPIRED ; 
 void* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 unsigned int GSSD_MIN_TIMEOUT ; 
 unsigned long HZ ; 
 scalar_t__ IS_ERR (void const*) ; 
 int /*<<< orphan*/  PTR_ERR (void const*) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int gss_import_sec_context (void const*,unsigned int,struct gss_api_mech*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 void* simple_get_bytes (void const*,void const*,...) ; 
 void* simple_get_netobj (void const*,void const*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static const void *
gss_fill_context(const void *p, const void *end, struct gss_cl_ctx *ctx, struct gss_api_mech *gm)
{
	const void *q;
	unsigned int seclen;
	unsigned int timeout;
	u32 window_size;
	int ret;

	/* First unsigned int gives the lifetime (in seconds) of the cred */
	p = simple_get_bytes(p, end, &timeout, sizeof(timeout));
	if (IS_ERR(p))
		goto err;
	if (timeout == 0)
		timeout = GSSD_MIN_TIMEOUT;
	ctx->gc_expiry = jiffies + (unsigned long)timeout * HZ * 3 / 4;
	/* Sequence number window. Determines the maximum number of simultaneous requests */
	p = simple_get_bytes(p, end, &window_size, sizeof(window_size));
	if (IS_ERR(p))
		goto err;
	ctx->gc_win = window_size;
	/* gssd signals an error by passing ctx->gc_win = 0: */
	if (ctx->gc_win == 0) {
		/*
		 * in which case, p points to an error code. Anything other
		 * than -EKEYEXPIRED gets converted to -EACCES.
		 */
		p = simple_get_bytes(p, end, &ret, sizeof(ret));
		if (!IS_ERR(p))
			p = (ret == -EKEYEXPIRED) ? ERR_PTR(-EKEYEXPIRED) :
						    ERR_PTR(-EACCES);
		goto err;
	}
	/* copy the opaque wire context */
	p = simple_get_netobj(p, end, &ctx->gc_wire_ctx);
	if (IS_ERR(p))
		goto err;
	/* import the opaque security context */
	p  = simple_get_bytes(p, end, &seclen, sizeof(seclen));
	if (IS_ERR(p))
		goto err;
	q = (const void *)((const char *)p + seclen);
	if (unlikely(q > end || q < p)) {
		p = ERR_PTR(-EFAULT);
		goto err;
	}
	ret = gss_import_sec_context(p, seclen, gm, &ctx->gc_gss_ctx, GFP_NOFS);
	if (ret < 0) {
		p = ERR_PTR(ret);
		goto err;
	}
	return q;
err:
	dprintk("RPC:       gss_fill_context returning %ld\n", -PTR_ERR(p));
	return p;
}