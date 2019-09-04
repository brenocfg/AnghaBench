#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct hmac_walker_ctx {int /*<<< orphan*/  hmac_ctx; } ;
typedef  int /*<<< orphan*/  mbuf_t ;
typedef  TYPE_2__* gss_buffer_t ;
typedef  TYPE_3__* crypto_ctx_t ;
struct TYPE_14__ {int output_size; } ;
struct TYPE_11__ {void** ikey; } ;
struct TYPE_13__ {int flags; int /*<<< orphan*/  digest_size; TYPE_8__* di; void** ckey; TYPE_1__ ks; int /*<<< orphan*/  lock; } ;
struct TYPE_12__ {int /*<<< orphan*/  value; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int CRYPTO_KS_ALLOCED ; 
 int EBADRPC ; 
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GSS_RCV ; 
 int GSS_SND ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  cc_key_schedule_create (TYPE_3__*) ; 
 int /*<<< orphan*/  cchmac_final (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cchmac_update (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_hmac ; 
 int /*<<< orphan*/  do_hmac_init (struct hmac_walker_ctx*,TYPE_3__*,void*) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int mbuf_walk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct hmac_walker_ctx*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
krb5_mic_mbuf(crypto_ctx_t ctx, gss_buffer_t header,
	      mbuf_t mbp, uint32_t offset, uint32_t len, gss_buffer_t trailer, uint8_t *mic, int *verify, int ikey, int reverse)
{
	struct hmac_walker_ctx wctx;
	uint8_t digest[ctx->di->output_size];
	int error;
	int kdx = (verify == NULL) ? (reverse ? GSS_RCV : GSS_SND) : (reverse ? GSS_SND : GSS_RCV);
	void *key2use;

	if (ikey) {
		if (!(ctx->flags & CRYPTO_KS_ALLOCED)) {
			lck_mtx_lock(ctx->lock);
			if (!(ctx->flags & CRYPTO_KS_ALLOCED)) {
				cc_key_schedule_create(ctx);
			}
			ctx->flags |= CRYPTO_KS_ALLOCED;
			lck_mtx_unlock(ctx->lock);
		}
		key2use = ctx->ks.ikey[kdx];
	} else {
		key2use = ctx->ckey[kdx];
	}

	do_hmac_init(&wctx, ctx, key2use);

	if (header) {
		cchmac_update(ctx->di, wctx.hmac_ctx, header->length, header->value);
	}

	error = mbuf_walk(mbp, offset, len, 1, do_hmac, &wctx);

	if (error)
		return (error);
	if (trailer)
		cchmac_update(ctx->di, wctx.hmac_ctx, trailer->length, trailer->value);

	cchmac_final(ctx->di, wctx.hmac_ctx, digest);
	FREE(wctx.hmac_ctx, M_TEMP);

	if (verify) {
		*verify = (memcmp(mic, digest, ctx->digest_size) == 0);
		if (!*verify)
			return (EBADRPC);
	} else
		memcpy(mic, digest, ctx->digest_size);

	return (0);
}