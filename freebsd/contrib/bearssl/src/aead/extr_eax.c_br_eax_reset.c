#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__* head; int /*<<< orphan*/  cbcmac; int /*<<< orphan*/  nonce; } ;
typedef  TYPE_1__ br_eax_context ;

/* Variables and functions */
 int /*<<< orphan*/  do_cbcmac_chunk (TYPE_1__*,void const*,size_t) ; 
 int /*<<< orphan*/  do_pad (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  omac_start (TYPE_1__*,int) ; 

void
br_eax_reset(br_eax_context *ctx, const void *nonce, size_t len)
{
	/*
	 * Process nonce with OMAC^0.
	 */
	omac_start(ctx, 0);
	do_cbcmac_chunk(ctx, nonce, len);
	do_pad(ctx);
	memcpy(ctx->nonce, ctx->cbcmac, sizeof ctx->cbcmac);

	/*
	 * Start OMAC^1 for the AAD ("header" in the EAX specification).
	 */
	omac_start(ctx, 1);

	/*
	 * We use ctx->head[0] as temporary flag to mark that we are
	 * using a "normal" reset().
	 */
	ctx->head[0] = 0;
}