#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int count_ctr; unsigned char* buf; int count_aad; int /*<<< orphan*/  j0_2; int /*<<< orphan*/  j0_1; TYPE_2__** bctx; int /*<<< orphan*/  y; int /*<<< orphan*/  h; int /*<<< orphan*/  (* gh ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int) ;} ;
typedef  TYPE_1__ br_gcm_context ;
struct TYPE_5__ {int /*<<< orphan*/  (* run ) (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  br_enc64be (unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 

void
br_gcm_get_tag(br_gcm_context *ctx, void *tag)
{
	size_t ptr;
	unsigned char tmp[16];

	ptr = (size_t)ctx->count_ctr & (size_t)15;
	if (ptr > 0) {
		/*
		 * There is a partial block: encrypted/decrypted data has
		 * been produced, but the encrypted bytes must still be
		 * processed by GHASH.
		 */
		ctx->gh(ctx->y, ctx->h, ctx->buf, ptr);
	}

	/*
	 * Final block for GHASH: the AAD and plaintext lengths (in bits).
	 */
	br_enc64be(tmp, ctx->count_aad << 3);
	br_enc64be(tmp + 8, ctx->count_ctr << 3);
	ctx->gh(ctx->y, ctx->h, tmp, 16);

	/*
	 * Tag is the GHASH output XORed with the encryption of the
	 * nonce with the initial counter value.
	 */
	memcpy(tag, ctx->y, 16);
	(*ctx->bctx)->run(ctx->bctx, ctx->j0_1, ctx->j0_2, tag, 16);
}