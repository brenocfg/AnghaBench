#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lucid_context_t ;
typedef  TYPE_3__* gss_ctx_id_t ;
struct TYPE_7__ {TYPE_3__* key_val; } ;
struct TYPE_8__ {TYPE_1__ key; } ;
struct TYPE_10__ {TYPE_2__ ctx_key; } ;
struct TYPE_9__ {TYPE_5__ gss_lucid_ctx; int /*<<< orphan*/  gss_cryptor; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  cc_clear (int,TYPE_5__*) ; 
 int /*<<< orphan*/  gss_crypto_ctx_free (int /*<<< orphan*/ *) ; 

void
gss_krb5_destroy_context(gss_ctx_id_t ctx)
{
	if (ctx == NULL)
		return;
	gss_crypto_ctx_free(&ctx->gss_cryptor);
	FREE(ctx->gss_lucid_ctx.ctx_key.key.key_val, M_TEMP);
	cc_clear(sizeof (lucid_context_t), &ctx->gss_lucid_ctx);
	FREE(ctx, M_TEMP);
}