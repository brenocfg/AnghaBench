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
typedef  int /*<<< orphan*/  u8 ;
struct shash_desc {int /*<<< orphan*/  tfm; } ;
struct ghash_desc_ctx {int bytes; int /*<<< orphan*/ * buffer; } ;
struct ghash_ctx {int /*<<< orphan*/  gf128; } ;
typedef  int /*<<< orphan*/  be128 ;

/* Variables and functions */
 int ENOKEY ; 
 int GHASH_BLOCK_SIZE ; 
 struct ghash_ctx* crypto_shash_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_xor (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  gf128mul_4k_lle (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int min (unsigned int,int) ; 
 struct ghash_desc_ctx* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int ghash_update(struct shash_desc *desc,
			 const u8 *src, unsigned int srclen)
{
	struct ghash_desc_ctx *dctx = shash_desc_ctx(desc);
	struct ghash_ctx *ctx = crypto_shash_ctx(desc->tfm);
	u8 *dst = dctx->buffer;

	if (!ctx->gf128)
		return -ENOKEY;

	if (dctx->bytes) {
		int n = min(srclen, dctx->bytes);
		u8 *pos = dst + (GHASH_BLOCK_SIZE - dctx->bytes);

		dctx->bytes -= n;
		srclen -= n;

		while (n--)
			*pos++ ^= *src++;

		if (!dctx->bytes)
			gf128mul_4k_lle((be128 *)dst, ctx->gf128);
	}

	while (srclen >= GHASH_BLOCK_SIZE) {
		crypto_xor(dst, src, GHASH_BLOCK_SIZE);
		gf128mul_4k_lle((be128 *)dst, ctx->gf128);
		src += GHASH_BLOCK_SIZE;
		srclen -= GHASH_BLOCK_SIZE;
	}

	if (srclen) {
		dctx->bytes = GHASH_BLOCK_SIZE - srclen;
		while (srclen--)
			*dst++ ^= *src++;
	}

	return 0;
}