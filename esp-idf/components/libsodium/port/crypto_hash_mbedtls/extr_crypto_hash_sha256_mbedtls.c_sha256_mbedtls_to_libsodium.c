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
struct TYPE_5__ {int /*<<< orphan*/  buffer; int /*<<< orphan*/  state; int /*<<< orphan*/  total; } ;
typedef  TYPE_1__ mbedtls_sha256_context ;
struct TYPE_6__ {int /*<<< orphan*/ * buf; int /*<<< orphan*/ * state; int /*<<< orphan*/  count; } ;
typedef  TYPE_2__ crypto_hash_sha256_state ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sha256_mbedtls_to_libsodium(crypto_hash_sha256_state *ls_state, const mbedtls_sha256_context *mb_ctx)
{
    memcpy(&ls_state->count, mb_ctx->total, sizeof(ls_state->count));
    memcpy(ls_state->state, mb_ctx->state, sizeof(ls_state->state));
    memcpy(ls_state->buf, mb_ctx->buffer, sizeof(ls_state->buf));
}