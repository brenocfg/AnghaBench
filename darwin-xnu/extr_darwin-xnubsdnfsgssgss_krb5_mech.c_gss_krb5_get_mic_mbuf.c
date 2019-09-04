#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  mbuf_t ;
typedef  TYPE_4__* lucid_context_version_t ;
typedef  int /*<<< orphan*/  gss_qop_t ;
typedef  TYPE_5__* gss_ctx_id_t ;
typedef  int /*<<< orphan*/  gss_buffer_t ;
struct TYPE_10__ {int proto; } ;
struct TYPE_11__ {TYPE_2__ key_data; } ;
struct TYPE_9__ {int /*<<< orphan*/  etype; } ;
struct TYPE_13__ {TYPE_3__ gss_lucid_ctx; TYPE_1__ gss_cryptor; } ;
struct TYPE_12__ {int version; } ;

/* Variables and functions */
 scalar_t__ ENOTSUP ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_FAILURE ; 
 scalar_t__ GSS_S_NO_CONTEXT ; 
 scalar_t__ gss_krb5_3des_get_mic_mbuf (scalar_t__*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ gss_krb5_cfx_get_mic_mbuf (scalar_t__*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  supported_etype (int,int /*<<< orphan*/ ) ; 

uint32_t
gss_krb5_get_mic_mbuf(uint32_t *minor,	/* minor_status */
		      gss_ctx_id_t ctx,	/* context_handle */
		      gss_qop_t qop,	/* qop_req */
		      mbuf_t mbp,	/* message mbuf */
		      size_t offset,	/* offest */
		      size_t len,	/* length */
		      gss_buffer_t mic	/* message_token */)
{
	uint32_t minor_stat = 0;

	if (minor == NULL)
		minor = &minor_stat;
	*minor = 0;

	if (len == 0)
		len = ~(size_t)0;

	/* Validate context */
	if (ctx == NULL || ((lucid_context_version_t)ctx)->version != 1)
		return (GSS_S_NO_CONTEXT);

	if (!supported_etype(ctx->gss_lucid_ctx.key_data.proto, ctx->gss_cryptor.etype)) {
		*minor = ENOTSUP;
		return (GSS_S_FAILURE);
	}

	switch(ctx->gss_lucid_ctx.key_data.proto) {
	case 0:
		/* RFC 1964 DES3 case */
		return (gss_krb5_3des_get_mic_mbuf(minor, ctx, qop, mbp, offset, len, mic));
	case 1:
		/* RFC 4121 CFX case */
		return (gss_krb5_cfx_get_mic_mbuf(minor, ctx, qop, mbp, offset, len, mic));
	}

	return (GSS_S_COMPLETE);
}