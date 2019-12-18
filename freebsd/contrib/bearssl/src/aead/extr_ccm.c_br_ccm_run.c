#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t ptr; unsigned int* buf; int /*<<< orphan*/  ctr; TYPE_2__** bctx; int /*<<< orphan*/  cbcmac; } ;
typedef  TYPE_1__ br_ccm_context ;
struct TYPE_8__ {int /*<<< orphan*/  (* ctr ) (TYPE_2__**,int /*<<< orphan*/ ,unsigned int*,int) ;int /*<<< orphan*/  (* encrypt ) (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,size_t) ;int /*<<< orphan*/  (* decrypt ) (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,size_t) ;int /*<<< orphan*/  (* mac ) (TYPE_2__**,int /*<<< orphan*/ ,unsigned int*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  memset (unsigned int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__**,int /*<<< orphan*/ ,unsigned int*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__**,int /*<<< orphan*/ ,unsigned int*,int) ; 

void
br_ccm_run(br_ccm_context *ctx, int encrypt, void *data, size_t len)
{
	unsigned char *dbuf;
	size_t ptr;

	dbuf = data;

	/*
	 * Complete a partial block, if any: ctx->buf[] contains
	 * ctx->ptr plaintext bytes (already reported), and the other
	 * bytes are CTR stream output.
	 */
	ptr = ctx->ptr;
	if (ptr != 0) {
		size_t clen;
		size_t u;

		clen = (sizeof ctx->buf) - ptr;
		if (clen > len) {
			clen = len;
		}
		if (encrypt) {
			for (u = 0; u < clen; u ++) {
				unsigned w, x;

				w = ctx->buf[ptr + u];
				x = dbuf[u];
				ctx->buf[ptr + u] = x;
				dbuf[u] = w ^ x;
			}
		} else {
			for (u = 0; u < clen; u ++) {
				unsigned w;

				w = ctx->buf[ptr + u] ^ dbuf[u];
				dbuf[u] = w;
				ctx->buf[ptr + u] = w;
			}
		}
		dbuf += clen;
		len -= clen;
		ptr += clen;
		if (ptr < sizeof ctx->buf) {
			ctx->ptr = ptr;
			return;
		}
		(*ctx->bctx)->mac(ctx->bctx,
			ctx->cbcmac, ctx->buf, sizeof ctx->buf);
	}

	/*
	 * Process all complete blocks. Note that the ctrcbc API is for
	 * encrypt-then-MAC (CBC-MAC is computed over the encrypted
	 * blocks) while CCM uses MAC-and-encrypt (CBC-MAC is computed
	 * over the plaintext blocks). Therefore, we need to use the
	 * _decryption_ function for encryption, and the encryption
	 * function for decryption (this works because CTR encryption
	 * and decryption are identical, so the choice really is about
	 * computing the CBC-MAC before or after XORing with the CTR
	 * stream).
	 */
	ptr = len & 15;
	len -= ptr;
	if (encrypt) {
		(*ctx->bctx)->decrypt(ctx->bctx, ctx->ctr, ctx->cbcmac,
			dbuf, len);
	} else {
		(*ctx->bctx)->encrypt(ctx->bctx, ctx->ctr, ctx->cbcmac,
			dbuf, len);
	}
	dbuf += len;

	/*
	 * If there is some remaining data, then we need to compute an
	 * extra block of CTR stream.
	 */
	if (ptr != 0) {
		size_t u;

		memset(ctx->buf, 0, sizeof ctx->buf);
		(*ctx->bctx)->ctr(ctx->bctx, ctx->ctr,
			ctx->buf, sizeof ctx->buf);
		if (encrypt) {
			for (u = 0; u < ptr; u ++) {
				unsigned w, x;

				w = ctx->buf[u];
				x = dbuf[u];
				ctx->buf[u] = x;
				dbuf[u] = w ^ x;
			}
		} else {
			for (u = 0; u < ptr; u ++) {
				unsigned w;

				w = ctx->buf[u] ^ dbuf[u];
				dbuf[u] = w;
				ctx->buf[u] = w;
			}
		}
	}
	ctx->ptr = ptr;
}