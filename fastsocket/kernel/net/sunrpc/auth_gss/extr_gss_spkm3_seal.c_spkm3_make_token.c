#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct xdr_netobj {int len; char* data; } ;
struct xdr_buf {int dummy; } ;
struct spkm3_ctx {int /*<<< orphan*/  mech_used; int /*<<< orphan*/  derived_integ_key; struct xdr_netobj ctx_id; int /*<<< orphan*/  conf_alg; int /*<<< orphan*/  intg_alg; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CKSUMTYPE_HMAC_MD5 ; 
 int /*<<< orphan*/  GSS_S_COMPLETE ; 
 int /*<<< orphan*/  GSS_S_FAILURE ; 
 int SPKM_MIC_TOK ; 
 int SPKM_WRAP_TOK ; 
 int /*<<< orphan*/  asn1_bitstring_len (struct xdr_netobj*,int*,int*) ; 
 int /*<<< orphan*/  cast5_cbc_oid ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  g_OID_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_make_token_header (int /*<<< orphan*/ *,int,unsigned char**) ; 
 int g_token_size (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hmac_md5_oid ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ make_spkm3_checksum (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int,struct xdr_buf*,int /*<<< orphan*/ ,struct xdr_netobj*) ; 
 int /*<<< orphan*/  spkm3_make_mic_token (unsigned char**,int,struct xdr_netobj*,struct xdr_netobj*,int,int) ; 
 int /*<<< orphan*/  spkm3_mic_header (char**,int*,unsigned char*,int,int) ; 

u32
spkm3_make_token(struct spkm3_ctx *ctx,
		   struct xdr_buf * text, struct xdr_netobj * token,
		   int toktype)
{
	s32			checksum_type;
	char			tokhdrbuf[25];
	char			cksumdata[16];
	struct xdr_netobj	md5cksum = {.len = 0, .data = cksumdata};
	struct xdr_netobj	mic_hdr = {.len = 0, .data = tokhdrbuf};
	int			tokenlen = 0;
	unsigned char		*ptr;
	s32			now;
	int			ctxelen = 0, ctxzbit = 0;
	int			md5elen = 0, md5zbit = 0;

	now = jiffies;

	if (ctx->ctx_id.len != 16) {
		dprintk("RPC:       spkm3_make_token BAD ctx_id.len %d\n",
				ctx->ctx_id.len);
		goto out_err;
	}

	if (!g_OID_equal(&ctx->intg_alg, &hmac_md5_oid)) {
		dprintk("RPC:       gss_spkm3_seal: unsupported I-ALG "
				"algorithm.  only support hmac-md5 I-ALG.\n");
		goto out_err;
	} else
		checksum_type = CKSUMTYPE_HMAC_MD5;

	if (!g_OID_equal(&ctx->conf_alg, &cast5_cbc_oid)) {
		dprintk("RPC:       gss_spkm3_seal: unsupported C-ALG "
				"algorithm\n");
		goto out_err;
	}

	if (toktype == SPKM_MIC_TOK) {
		/* Calculate checksum over the mic-header */
		asn1_bitstring_len(&ctx->ctx_id, &ctxelen, &ctxzbit);
		spkm3_mic_header(&mic_hdr.data, &mic_hdr.len, ctx->ctx_id.data,
				ctxelen, ctxzbit);
		if (make_spkm3_checksum(checksum_type, &ctx->derived_integ_key,
					(char *)mic_hdr.data, mic_hdr.len,
					text, 0, &md5cksum))
			goto out_err;

		asn1_bitstring_len(&md5cksum, &md5elen, &md5zbit);
		tokenlen = 10 + ctxelen + 1 + md5elen + 1;

		/* Create token header using generic routines */
		token->len = g_token_size(&ctx->mech_used, tokenlen + 2);

		ptr = token->data;
		g_make_token_header(&ctx->mech_used, tokenlen + 2, &ptr);

		spkm3_make_mic_token(&ptr, tokenlen, &mic_hdr, &md5cksum, md5elen, md5zbit);
	} else if (toktype == SPKM_WRAP_TOK) { /* Not Supported */
		dprintk("RPC:       gss_spkm3_seal: SPKM_WRAP_TOK "
				"not supported\n");
		goto out_err;
	}

	/* XXX need to implement sequence numbers, and ctx->expired */

	return  GSS_S_COMPLETE;
out_err:
	token->data = NULL;
	token->len = 0;
	return GSS_S_FAILURE;
}