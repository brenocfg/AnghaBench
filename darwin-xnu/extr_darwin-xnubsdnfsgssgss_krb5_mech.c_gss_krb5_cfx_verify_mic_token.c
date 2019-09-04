#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  TYPE_4__* lucid_context_t ;
typedef  TYPE_5__* gss_ctx_id_t ;
typedef  TYPE_6__* gss_cfx_mic_token ;
struct TYPE_16__ {scalar_t__* TOK_ID; scalar_t__* Filler; } ;
struct TYPE_15__ {scalar_t__* TOK_ID; int Flags; scalar_t__* Filler; } ;
struct TYPE_10__ {scalar_t__ acceptor_subkey; } ;
struct TYPE_11__ {TYPE_1__ data_4121; } ;
struct TYPE_12__ {TYPE_2__ lucid_protocol_u; } ;
struct TYPE_13__ {TYPE_3__ key_data; scalar_t__ initiate; } ;
struct TYPE_14__ {TYPE_4__ gss_lucid_ctx; } ;

/* Variables and functions */
 int CFXAcceptorSubkey ; 
 int CFXSentByAcceptor ; 
 int EBADRPC ; 
 TYPE_7__ mic_cfx_token ; 
 int /*<<< orphan*/  printf (char*,scalar_t__,int) ; 

__attribute__((used)) static int
gss_krb5_cfx_verify_mic_token(gss_ctx_id_t ctx, gss_cfx_mic_token token)
{
	int i;
	lucid_context_t lctx = &ctx->gss_lucid_ctx;
	uint8_t flags = 0;

	if (token->TOK_ID[0] != mic_cfx_token.TOK_ID[0] || token->TOK_ID[1] != mic_cfx_token.TOK_ID[1]) {
		printf("Bad mic TOK_ID %x %x\n", token->TOK_ID[0], token->TOK_ID[1]);
		return (EBADRPC);
	}
	if (lctx->initiate)
		flags |= CFXSentByAcceptor;
	if (lctx->key_data.lucid_protocol_u.data_4121.acceptor_subkey)
		flags |= CFXAcceptorSubkey;
	if (token->Flags != flags) {
		printf("Bad flags received %x exptect %x\n", token->Flags, flags);
		return (EBADRPC);
	}
	for (i = 0; i < 5; i++) {
		if (token->Filler[i] != mic_cfx_token.Filler[i])
			break;
	}

	if (i != 5) {
		printf("Bad mic filler %x @ %d\n", token->Filler[i], i);
		return (EBADRPC);
	}

	return (0);
}