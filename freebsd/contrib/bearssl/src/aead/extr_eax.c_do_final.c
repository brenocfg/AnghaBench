#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* cbcmac; int* nonce; int* head; } ;
typedef  TYPE_1__ br_eax_context ;

/* Variables and functions */
 int /*<<< orphan*/  do_pad (TYPE_1__*) ; 

__attribute__((used)) static void
do_final(br_eax_context *ctx)
{
	size_t u;

	do_pad(ctx);

	/*
	 * Authentication tag is the XOR of the three OMAC outputs for
	 * the nonce, AAD and encrypted data.
	 */
	for (u = 0; u < 16; u ++) {
		ctx->cbcmac[u] ^= ctx->nonce[u] ^ ctx->head[u];
	}
}