#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct crypt_walker_ctx {int /*<<< orphan*/  iv; int /*<<< orphan*/  crypt_ctx; } ;
struct ccmode_cbc {int block_size; } ;
typedef  scalar_t__ mbuf_t ;
typedef  int errno_t ;
typedef  int /*<<< orphan*/  cts_pad ;
typedef  TYPE_2__* crypto_ctx_t ;
typedef  int /*<<< orphan*/  (* ccpad_func ) (struct ccmode_cbc const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  cccbc_ctx ;
typedef  int /*<<< orphan*/  block ;
struct TYPE_6__ {int /*<<< orphan*/ * dec; int /*<<< orphan*/ * enc; } ;
struct TYPE_7__ {int flags; int mpad; TYPE_1__ ks; int /*<<< orphan*/  lock; struct ccmode_cbc* dec_mode; struct ccmode_cbc* enc_mode; } ;

/* Variables and functions */
 int CRYPTO_CTS_ENABLE ; 
 int CRYPTO_KS_ALLOCED ; 
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cc_key_schedule_create (TYPE_2__*) ; 
 int /*<<< orphan*/  ccpad_cts3_decrypt (struct ccmode_cbc const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ccpad_cts3_encrypt (struct ccmode_cbc const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_crypt ; 
 int /*<<< orphan*/  do_crypt_init (struct crypt_walker_ctx*,int,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int gss_append_mbuf (scalar_t__,int /*<<< orphan*/ *,size_t) ; 
 size_t gss_mbuf_len (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gss_normalize_mbuf (scalar_t__,int /*<<< orphan*/ ,size_t*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbuf_copydata (scalar_t__,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbuf_freem (scalar_t__) ; 
 int mbuf_walk (scalar_t__,int /*<<< orphan*/ ,size_t,int,int /*<<< orphan*/ ,struct crypt_walker_ctx*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

errno_t  /* __attribute__((optnone)) */
krb5_crypt_mbuf(crypto_ctx_t ctx, mbuf_t *mbp, uint32_t len, int encrypt, cccbc_ctx *ks)
{
	struct crypt_walker_ctx wctx;
	const struct ccmode_cbc *ccmode = encrypt ? ctx->enc_mode : ctx->dec_mode;
	size_t plen = len;
	size_t cts_len = 0;
	mbuf_t mb, lmb;
	int error;

	if (!(ctx->flags & CRYPTO_KS_ALLOCED)) {
		lck_mtx_lock(ctx->lock);
		if (!(ctx->flags & CRYPTO_KS_ALLOCED)) {
			cc_key_schedule_create(ctx);
		}
		ctx->flags |= CRYPTO_KS_ALLOCED;
		lck_mtx_unlock(ctx->lock);
	}
	if (!ks)
		ks = encrypt ? ctx->ks.enc : ctx->ks.dec;

	if ((ctx->flags & CRYPTO_CTS_ENABLE) && ctx->mpad == 1) {
		uint8_t block[ccmode->block_size];
		/* if the length is less than or equal to a blocksize. We just encrypt the block */
		if (len <= ccmode->block_size) {
			if (len < ccmode->block_size) {
				memset(block, 0, sizeof(block));
				gss_append_mbuf(*mbp, block, ccmode->block_size);
			}
			plen = ccmode->block_size;
		} else {
			/* determine where the last two blocks are */
			uint32_t r = len % ccmode->block_size;

			cts_len  = r ? r + ccmode->block_size : 2 * ccmode->block_size;
			plen = len - cts_len;
			/* If plen is 0 we only have two blocks to crypt with ccpad below */
			if (plen == 0)
				lmb = *mbp;
			else {
				gss_normalize_mbuf(*mbp, 0, &plen, &mb, &lmb, 0);
				assert(*mbp == mb);
				assert(plen == len - cts_len);
				assert(gss_mbuf_len(mb, 0) == plen);
				assert(gss_mbuf_len(lmb, 0) == cts_len);
			}
		}
	} else if (len % ctx->mpad) {
		uint8_t pad_block[ctx->mpad];
		size_t padlen = ctx->mpad - (len % ctx->mpad);

		memset(pad_block, 0, padlen);
		error = gss_append_mbuf(*mbp, pad_block, padlen);
		if (error)
			return (error);
		plen = len + padlen;
	}
	do_crypt_init(&wctx, encrypt, ctx, ks);
	if (plen) {
		error = mbuf_walk(*mbp, 0, plen, ccmode->block_size, do_crypt, &wctx);
		if (error)
			return (error);
	}

	if ((ctx->flags & CRYPTO_CTS_ENABLE) && cts_len) {
		uint8_t cts_pad[2*ccmode->block_size];
		ccpad_func do_ccpad = encrypt ? ccpad_cts3_encrypt : ccpad_cts3_decrypt;

		assert(cts_len <= 2*ccmode->block_size && cts_len > ccmode->block_size);
		memset(cts_pad, 0, sizeof(cts_pad));
		mbuf_copydata(lmb, 0, cts_len, cts_pad);
		mbuf_freem(lmb);
		do_ccpad(ccmode, wctx.crypt_ctx, wctx.iv, cts_len, cts_pad, cts_pad);
		gss_append_mbuf(*mbp, cts_pad, cts_len);
	}
	FREE(wctx.iv, M_TEMP);

	return (0);
}