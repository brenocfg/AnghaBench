#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  mbuf_t ;
typedef  TYPE_1__* lucid_context_t ;
typedef  int /*<<< orphan*/  gss_qop_t ;
typedef  TYPE_2__* gss_ctx_id_t ;
typedef  int /*<<< orphan*/  gss_cfx_mic_token_desc ;
typedef  TYPE_3__* gss_cfx_mic_token ;
typedef  TYPE_4__* gss_buffer_t ;
struct TYPE_15__ {int length; TYPE_3__* value; } ;
typedef  TYPE_5__ gss_buffer_desc ;
typedef  int /*<<< orphan*/ * crypto_ctx_t ;
struct TYPE_14__ {TYPE_3__* value; } ;
struct TYPE_13__ {int /*<<< orphan*/  SND_SEQ; } ;
struct TYPE_11__ {int /*<<< orphan*/  recv_seq; } ;
struct TYPE_12__ {int /*<<< orphan*/  gss_cryptor; TYPE_1__ gss_lucid_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_C_QOP_DEFAULT ; 
 int /*<<< orphan*/  GSS_S_BAD_SIG ; 
 int /*<<< orphan*/  GSS_S_COMPLETE ; 
 int /*<<< orphan*/  GSS_S_FAILURE ; 
 int /*<<< orphan*/  gss_krb5_cfx_verify_mic_token (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  krb5_mic_mbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,size_t,TYPE_5__*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntohll (int /*<<< orphan*/ ) ; 

uint32_t
gss_krb5_cfx_verify_mic_mbuf(uint32_t *minor,	/* minor_status */
			     gss_ctx_id_t ctx,	/* context_handle */
			     mbuf_t mbp,		/* message_buffer */
			     size_t offset,		/* offset */
			     size_t len,		/* length */
			     gss_buffer_t mic,	/* message_token */
			     gss_qop_t *qop		/* qop_state */)
{
	gss_cfx_mic_token token = mic->value;
	lucid_context_t lctx = &ctx->gss_lucid_ctx;
	crypto_ctx_t cctx = &ctx->gss_cryptor;
	uint8_t *digest = (uint8_t *)mic->value + sizeof (gss_cfx_mic_token_desc);
	int verified;
	uint64_t seq;
	uint32_t rv;
	gss_buffer_desc header;

	if (qop)
		*qop = GSS_C_QOP_DEFAULT;

	if (minor == NULL)
		minor = &rv;

	*minor = gss_krb5_cfx_verify_mic_token(ctx, token);
	if (*minor)
		return (GSS_S_FAILURE);

	header.length = sizeof(gss_cfx_mic_token_desc);
	header.value = mic->value;

	*minor = krb5_mic_mbuf(cctx, NULL, mbp, offset, len, &header, digest, &verified, 0, 0);

	//XXX  errors and such? Sequencing and replay? Not Supported RPCSEC_GSS
	memcpy(&seq, token->SND_SEQ, sizeof (uint64_t));
	seq = ntohll(seq);
	lctx->recv_seq = seq;

	return (verified ? GSS_S_COMPLETE : GSS_S_BAD_SIG);
}