#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct xdr_netobj {int len; char* data; } ;
struct xdr_buf {int dummy; } ;
struct krb5_ctx {scalar_t__ endtime; scalar_t__ initiate; TYPE_1__* gk5e; int /*<<< orphan*/ * cksum; int /*<<< orphan*/  mech_used; } ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  cksumdata ;
struct TYPE_2__ {int signalg; int /*<<< orphan*/  cksumlength; scalar_t__ keyed_cksum; } ;

/* Variables and functions */
 int GSS_KRB5_MAX_CKSUM_LEN ; 
 int GSS_KRB5_TOK_HDR_LEN ; 
 int /*<<< orphan*/  GSS_S_BAD_SIG ; 
 int /*<<< orphan*/  GSS_S_COMPLETE ; 
 int /*<<< orphan*/  GSS_S_CONTEXT_EXPIRED ; 
 int /*<<< orphan*/  GSS_S_DEFECTIVE_TOKEN ; 
 int /*<<< orphan*/  GSS_S_FAILURE ; 
 int KG_TOK_MIC_MSG ; 
 int /*<<< orphan*/  KG_USAGE_SIGN ; 
 int SEAL_ALG_NONE ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 scalar_t__ g_verify_token_header (int /*<<< orphan*/ *,int*,unsigned char**,int) ; 
 scalar_t__ get_seconds () ; 
 scalar_t__ krb5_get_seq_num (struct krb5_ctx*,unsigned char*,unsigned char*,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ make_checksum (struct krb5_ctx*,unsigned char*,int,struct xdr_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct xdr_netobj*) ; 
 scalar_t__ memcmp (char*,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32
gss_verify_mic_v1(struct krb5_ctx *ctx,
		struct xdr_buf *message_buffer, struct xdr_netobj *read_token)
{
	int			signalg;
	int			sealalg;
	char			cksumdata[GSS_KRB5_MAX_CKSUM_LEN];
	struct xdr_netobj	md5cksum = {.len = sizeof(cksumdata),
					    .data = cksumdata};
	s32			now;
	int			direction;
	u32			seqnum;
	unsigned char		*ptr = (unsigned char *)read_token->data;
	int			bodysize;
	u8			*cksumkey;

	dprintk("RPC:       krb5_read_token\n");

	if (g_verify_token_header(&ctx->mech_used, &bodysize, &ptr,
					read_token->len))
		return GSS_S_DEFECTIVE_TOKEN;

	if ((ptr[0] != ((KG_TOK_MIC_MSG >> 8) & 0xff)) ||
	    (ptr[1] !=  (KG_TOK_MIC_MSG & 0xff)))
		return GSS_S_DEFECTIVE_TOKEN;

	/* XXX sanity-check bodysize?? */

	signalg = ptr[2] + (ptr[3] << 8);
	if (signalg != ctx->gk5e->signalg)
		return GSS_S_DEFECTIVE_TOKEN;

	sealalg = ptr[4] + (ptr[5] << 8);
	if (sealalg != SEAL_ALG_NONE)
		return GSS_S_DEFECTIVE_TOKEN;

	if ((ptr[6] != 0xff) || (ptr[7] != 0xff))
		return GSS_S_DEFECTIVE_TOKEN;

	if (ctx->gk5e->keyed_cksum)
		cksumkey = ctx->cksum;
	else
		cksumkey = NULL;

	if (make_checksum(ctx, ptr, 8, message_buffer, 0,
			  cksumkey, KG_USAGE_SIGN, &md5cksum))
		return GSS_S_FAILURE;

	if (memcmp(md5cksum.data, ptr + GSS_KRB5_TOK_HDR_LEN,
					ctx->gk5e->cksumlength))
		return GSS_S_BAD_SIG;

	/* it got through unscathed.  Make sure the context is unexpired */

	now = get_seconds();

	if (now > ctx->endtime)
		return GSS_S_CONTEXT_EXPIRED;

	/* do sequencing checks */

	if (krb5_get_seq_num(ctx, ptr + GSS_KRB5_TOK_HDR_LEN, ptr + 8,
			     &direction, &seqnum))
		return GSS_S_FAILURE;

	if ((ctx->initiate && direction != 0xff) ||
	    (!ctx->initiate && direction != 0))
		return GSS_S_BAD_SIG;

	return GSS_S_COMPLETE;
}