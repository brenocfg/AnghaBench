#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  TYPE_1__* lucid_context_t ;
typedef  int /*<<< orphan*/  gss_qop_t ;
typedef  TYPE_2__* gss_ctx_id_t ;
typedef  int /*<<< orphan*/  gss_cfx_mic_token_desc ;
typedef  TYPE_3__* gss_cfx_mic_token ;
typedef  TYPE_4__* gss_buffer_t ;
struct TYPE_19__ {int length; TYPE_3__* value; } ;
typedef  TYPE_5__ gss_buffer_desc ;
typedef  TYPE_6__* crypto_ctx_t ;
struct TYPE_20__ {scalar_t__ digest_size; } ;
struct TYPE_18__ {scalar_t__ length; TYPE_3__* value; } ;
struct TYPE_17__ {int /*<<< orphan*/  SND_SEQ; } ;
struct TYPE_15__ {int /*<<< orphan*/  recv_seq; } ;
struct TYPE_16__ {TYPE_6__ gss_cryptor; TYPE_1__ gss_lucid_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBADRPC ; 
 int /*<<< orphan*/  GSS_C_QOP_DEFAULT ; 
 int /*<<< orphan*/  GSS_S_BAD_SIG ; 
 int /*<<< orphan*/  GSS_S_COMPLETE ; 
 int /*<<< orphan*/  GSS_S_FAILURE ; 
 int /*<<< orphan*/  gss_krb5_cfx_verify_mic_token (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  krb5_mic (TYPE_6__*,int /*<<< orphan*/ *,TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntohll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

uint32_t
gss_krb5_cfx_verify_mic(uint32_t *minor,	/* minor_status */
			gss_ctx_id_t ctx,	/* context_handle */
			gss_buffer_t mbp,	/* message_buffer */
			gss_buffer_t mic,	/* message_token */
			gss_qop_t *qop		/* qop_state */)
{
	gss_cfx_mic_token token = mic->value;
	lucid_context_t lctx = &ctx->gss_lucid_ctx;
	crypto_ctx_t cctx = &ctx->gss_cryptor;
	uint8_t *digest = (uint8_t *)mic->value + sizeof (gss_cfx_mic_token_desc);
	int verified = 0;
	uint64_t seq;
	uint32_t rv;
	gss_buffer_desc header;

	if (qop)
		*qop = GSS_C_QOP_DEFAULT;
	if (minor == NULL)
		minor = &rv;

	if (mic->length != sizeof(gss_cfx_mic_token_desc) + cctx->digest_size) {
		printf("mic token wrong length\n");
		*minor = EBADRPC;
		goto out;
	}
	*minor = gss_krb5_cfx_verify_mic_token(ctx, token);
	if (*minor)
		return (GSS_S_FAILURE);
	header.value = token;
	header.length = sizeof (gss_cfx_mic_token_desc);
	*minor = krb5_mic(cctx, NULL, mbp, &header, digest, &verified, 0, 0);

	if (verified) {
		//XXX  errors and such? Sequencing and replay? Not supported in RPCSEC_GSS
		memcpy(&seq, token->SND_SEQ, sizeof (uint64_t));
		seq = ntohll(seq);
		lctx->recv_seq = seq;
	}

out:
	return (verified ? GSS_S_COMPLETE : GSS_S_BAD_SIG);
}