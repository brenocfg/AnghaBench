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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/ * mbuf_t ;
typedef  TYPE_4__* lucid_context_version_t ;
typedef  int /*<<< orphan*/  gss_qop_t ;
typedef  TYPE_5__* gss_ctx_id_t ;
struct TYPE_10__ {int proto; } ;
struct TYPE_11__ {TYPE_2__ key_data; } ;
struct TYPE_9__ {int /*<<< orphan*/  etype; } ;
struct TYPE_13__ {TYPE_3__ gss_lucid_ctx; TYPE_1__ gss_cryptor; } ;
struct TYPE_12__ {int version; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  GSS_C_QOP_DEFAULT ; 
 int /*<<< orphan*/  GSS_S_FAILURE ; 
 int /*<<< orphan*/  GSS_S_NO_CONTEXT ; 
 int /*<<< orphan*/  gss_join_mbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gss_krb5_3des_unwrap_mbuf (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ **,size_t,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gss_krb5_cfx_unwrap_mbuf (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ **,size_t,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gss_normalize_mbuf (int /*<<< orphan*/ *,size_t,size_t*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  supported_etype (int,int /*<<< orphan*/ ) ; 

uint32_t
gss_krb5_unwrap_mbuf(uint32_t * minor,		/* minor_status */
		     gss_ctx_id_t ctx,		/* context_handle */
		     mbuf_t *mbp,		/* input/output message_buffer */
		     size_t offset,		/* offset */
		     size_t len,		/* length */
		     int *conf_flag,		/* conf_state */
		     gss_qop_t *qop		/* qop state */)
{
	uint32_t major, minor_stat = 0;
	gss_qop_t qop_val = GSS_C_QOP_DEFAULT;
	int conf_val = 0;
	mbuf_t smb, tmb;

	if (minor == NULL)
		minor = &minor_stat;
	if (qop == NULL)
		qop = &qop_val;
	if (conf_flag == NULL)
		conf_flag = &conf_val;

	/* Validate context */
	if (ctx == NULL || ((lucid_context_version_t)ctx)->version != 1)
		return (GSS_S_NO_CONTEXT);

	if (!supported_etype(ctx->gss_lucid_ctx.key_data.proto, ctx->gss_cryptor.etype)) {
		*minor = ENOTSUP;
		return (GSS_S_FAILURE);
	}

	gss_normalize_mbuf(*mbp, offset, &len, &smb, &tmb, 0);

	switch(ctx->gss_lucid_ctx.key_data.proto) {
	case 0:
		/* RFC 1964 DES3 case */
		major = gss_krb5_3des_unwrap_mbuf(minor, ctx, &smb, len, conf_flag, qop);
		break;
	case 1:
		/* RFC 4121 CFX case */
		major = gss_krb5_cfx_unwrap_mbuf(minor, ctx, &smb, len, conf_flag, qop);
		break;
	}

	if (offset)
		gss_join_mbuf(*mbp, smb, tmb);
	else {
		*mbp = smb;
		gss_join_mbuf(smb, tmb, NULL);
	}

	return (major);
}