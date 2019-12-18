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
struct TYPE_7__ {size_t ptr; unsigned char* buf; int /*<<< orphan*/  ctr; TYPE_2__** bctx; int /*<<< orphan*/  cbcmac; } ;
typedef  TYPE_1__ br_eax_context ;
struct TYPE_8__ {int /*<<< orphan*/  (* ctr ) (TYPE_2__**,int /*<<< orphan*/ ,unsigned int*,int) ;int /*<<< orphan*/  (* decrypt ) (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,size_t) ;int /*<<< orphan*/  (* encrypt ) (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,size_t) ;int /*<<< orphan*/  (* mac ) (TYPE_2__**,int /*<<< orphan*/ ,unsigned int*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  memset (unsigned int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__**,int /*<<< orphan*/ ,unsigned int*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__**,int /*<<< orphan*/ ,unsigned int*,int) ; 

void
br_eax_run(br_eax_context *ctx, int encrypt, void *data, size_t len)
{
	unsigned char *dbuf;
	size_t ptr;

	/*
	 * Ensure that there is actual data to process.
	 */
	if (len == 0) {
		return;
	}

	dbuf = data;
	ptr = ctx->ptr;

	/*
	 * We may have ptr == 0 here if we initialized from a captured
	 * state. In that case, there is no partially consumed block
	 * or unprocessed data.
	 */
	if (ptr != 0 && ptr != 16) {
		/*
		 * We have a partially consumed block.
		 */
		size_t u, clen;

		clen = 16 - ptr;
		if (len <= clen) {
			clen = len;
		}
		if (encrypt) {
			for (u = 0; u < clen; u ++) {
				ctx->buf[ptr + u] ^= dbuf[u];
			}
			memcpy(dbuf, ctx->buf + ptr, clen);
		} else {
			for (u = 0; u < clen; u ++) {
				unsigned dx, sx;

				sx = ctx->buf[ptr + u];
				dx = dbuf[u];
				ctx->buf[ptr + u] = dx;
				dbuf[u] = sx ^ dx;
			}
		}

		if (len <= clen) {
			ctx->ptr = ptr + clen;
			return;
		}
		dbuf += clen;
		len -= clen;
	}

	/*
	 * We now have a complete encrypted block in buf[] that must still
	 * be processed with OMAC, and this is not the final buf.
	 * Exception: when ptr == 0, no block has been produced yet.
	 */
	if (ptr != 0) {
		(*ctx->bctx)->mac(ctx->bctx, ctx->cbcmac,
			ctx->buf, sizeof ctx->buf);
	}

	/*
	 * Do CTR encryption or decryption and CBC-MAC for all full blocks
	 * except the last.
	 */
	ptr = len & (size_t)15;
	if (ptr == 0) {
		len -= 16;
		ptr = 16;
	} else {
		len -= ptr;
	}
	if (encrypt) {
		(*ctx->bctx)->encrypt(ctx->bctx, ctx->ctr, ctx->cbcmac,
			dbuf, len);
	} else {
		(*ctx->bctx)->decrypt(ctx->bctx, ctx->ctr, ctx->cbcmac,
			dbuf, len);
	}
	dbuf += len;

	/*
	 * Compute next block of CTR stream, and use it to finish
	 * encrypting or decrypting the data.
	 */
	memset(ctx->buf, 0, sizeof ctx->buf);
	(*ctx->bctx)->ctr(ctx->bctx, ctx->ctr, ctx->buf, sizeof ctx->buf);
	if (encrypt) {
		size_t u;

		for (u = 0; u < ptr; u ++) {
			ctx->buf[u] ^= dbuf[u];
		}
		memcpy(dbuf, ctx->buf, ptr);
	} else {
		size_t u;

		for (u = 0; u < ptr; u ++) {
			unsigned dx, sx;

			sx = ctx->buf[u];
			dx = dbuf[u];
			ctx->buf[u] = dx;
			dbuf[u] = sx ^ dx;
		}
	}
	ctx->ptr = ptr;
}