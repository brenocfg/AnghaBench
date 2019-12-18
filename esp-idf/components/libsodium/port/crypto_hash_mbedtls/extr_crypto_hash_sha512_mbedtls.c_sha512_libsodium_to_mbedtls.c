#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ is384; int /*<<< orphan*/  buffer; int /*<<< orphan*/  state; int /*<<< orphan*/  total; } ;
typedef  TYPE_1__ mbedtls_sha512_context ;
struct TYPE_6__ {int /*<<< orphan*/  buf; int /*<<< orphan*/  state; int /*<<< orphan*/  count; } ;
typedef  TYPE_2__ crypto_hash_sha512_state ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sha512_libsodium_to_mbedtls(mbedtls_sha512_context *mb_ctx, crypto_hash_sha512_state *ls_state)
{
    memcpy(mb_ctx->total, ls_state->count, sizeof(mb_ctx->total));
    memcpy(mb_ctx->state, ls_state->state, sizeof(mb_ctx->state));
    memcpy(mb_ctx->buffer, ls_state->buf, sizeof(mb_ctx->buffer));
    mb_ctx->is384 = 0;
}