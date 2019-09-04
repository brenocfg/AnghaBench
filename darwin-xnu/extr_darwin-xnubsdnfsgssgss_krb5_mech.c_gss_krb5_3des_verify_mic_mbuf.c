#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int* Sign_Alg; } ;
typedef  TYPE_1__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  mbuf_t ;
typedef  int /*<<< orphan*/  gss_qop_t ;
typedef  TYPE_2__* gss_ctx_id_t ;
typedef  int /*<<< orphan*/  gss_buffer_t ;
struct TYPE_16__ {int length; TYPE_1__* value; } ;
typedef  TYPE_3__ gss_buffer_desc ;
typedef  TYPE_1__ gss_1964_mic_token_desc ;
typedef  TYPE_5__* crypto_ctx_t ;
struct TYPE_17__ {int digest_size; } ;
struct TYPE_15__ {TYPE_5__ gss_cryptor; } ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_C_QOP_DEFAULT ; 
 int /*<<< orphan*/  GSS_S_BAD_SIG ; 
 int /*<<< orphan*/  GSS_S_COMPLETE ; 
 int /*<<< orphan*/  GSS_S_FAILURE ; 
 int /*<<< orphan*/  gss_krb5_3des_token_get (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_mic_mbuf (TYPE_5__*,TYPE_3__*,int /*<<< orphan*/ ,size_t,size_t,int /*<<< orphan*/ *,TYPE_1__*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ mic_1964_token ; 

uint32_t
gss_krb5_3des_verify_mic_mbuf(uint32_t *minor,
			      gss_ctx_id_t ctx,
			      mbuf_t mbp,
			      size_t offset,
			      size_t len,
			      gss_buffer_t mic,
			      gss_qop_t *qop)
{
	crypto_ctx_t cctx = &ctx->gss_cryptor;
	uint8_t hashval[cctx->digest_size];
	gss_buffer_desc header;
	gss_buffer_desc hash;
	gss_1964_mic_token_desc mtok = mic_1964_token;
	int verf;

	mtok.Sign_Alg[0] = 0x04; /* lctx->key_data.lucic_protocol_u.data1964.sign_alg */
	mtok.Sign_Alg[1] = 0x00;
	hash.length = cctx->digest_size;
	hash.value = hashval;
	header.length = sizeof(gss_1964_mic_token_desc);
	header.value = &mtok;

	if (qop)
		*qop = GSS_C_QOP_DEFAULT;

	*minor = gss_krb5_3des_token_get(ctx, mic, mtok, &hash, NULL, NULL, 0);
	if (*minor)
		return (GSS_S_FAILURE);

	*minor = krb5_mic_mbuf(cctx, &header, mbp, offset, len, NULL, hashval, &verf, 0, 0);
	if (*minor)
		return (GSS_S_FAILURE);

	return (verf ? GSS_S_COMPLETE : GSS_S_BAD_SIG);
}