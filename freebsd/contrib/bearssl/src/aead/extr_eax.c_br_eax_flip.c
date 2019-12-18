#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* head; int* cbcmac; int* ctr; int* nonce; scalar_t__ ptr; } ;
typedef  TYPE_1__ br_eax_context ;

/* Variables and functions */
 int /*<<< orphan*/  do_pad (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  omac_start (TYPE_1__*,int) ; 

void
br_eax_flip(br_eax_context *ctx)
{
	int from_capture;

	/*
	 * ctx->head[0] may be non-zero if the context was reset with
	 * a pre-AAD captured state. In that case, ctx->ctr[] contains
	 * the state for OMAC^2 _after_ processing the first block.
	 */
	from_capture = ctx->head[0];

	/*
	 * Complete the OMAC computation on the AAD.
	 */
	do_pad(ctx);
	memcpy(ctx->head, ctx->cbcmac, sizeof ctx->cbcmac);

	/*
	 * Start OMAC^2 for the encrypted data.
	 * If the context was initialized from a captured state, then
	 * the OMAC^2 value is in the ctr[] array.
	 */
	if (from_capture) {
		memcpy(ctx->cbcmac, ctx->ctr, sizeof ctx->cbcmac);
		ctx->ptr = 0;
	} else {
		omac_start(ctx, 2);
	}

	/*
	 * Initial counter value for CTR is the processed nonce.
	 */
	memcpy(ctx->ctr, ctx->nonce, sizeof ctx->nonce);
}