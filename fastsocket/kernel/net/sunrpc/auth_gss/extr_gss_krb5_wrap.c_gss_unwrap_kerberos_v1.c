#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char u8 ;
typedef  int u32 ;
struct xdr_netobj {int len; char* data; } ;
struct xdr_buf {scalar_t__ len; TYPE_2__* head; } ;
struct krb5_ctx {scalar_t__ enctype; unsigned char* cksum; scalar_t__ endtime; TYPE_1__* gk5e; struct crypto_blkcipher* enc; scalar_t__ initiate; int /*<<< orphan*/  mech_used; } ;
struct crypto_blkcipher {int dummy; } ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  cksumdata ;
struct TYPE_4__ {void* iov_base; int iov_len; } ;
struct TYPE_3__ {int conflen; int signalg; int sealalg; int cksumlength; scalar_t__ keyed_cksum; int /*<<< orphan*/  encrypt_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_ASYNC ; 
 scalar_t__ ENCTYPE_ARCFOUR_HMAC ; 
 int GSS_KRB5_MAX_CKSUM_LEN ; 
 int GSS_KRB5_TOK_HDR_LEN ; 
 int GSS_S_BAD_SIG ; 
 int GSS_S_COMPLETE ; 
 int GSS_S_CONTEXT_EXPIRED ; 
 int GSS_S_DEFECTIVE_TOKEN ; 
 int GSS_S_FAILURE ; 
 scalar_t__ IS_ERR (struct crypto_blkcipher*) ; 
 int KG_TOK_WRAP_MSG ; 
 int /*<<< orphan*/  KG_USAGE_SEAL ; 
 struct crypto_blkcipher* crypto_alloc_blkcipher (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int crypto_blkcipher_blocksize (struct crypto_blkcipher*) ; 
 int /*<<< orphan*/  crypto_free_blkcipher (struct crypto_blkcipher*) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 scalar_t__ g_verify_token_header (int /*<<< orphan*/ *,int*,unsigned char**,scalar_t__) ; 
 scalar_t__ get_seconds () ; 
 int gss_decrypt_xdr_buf (struct crypto_blkcipher*,struct xdr_buf*,int) ; 
 scalar_t__ gss_krb5_remove_padding (struct xdr_buf*,int) ; 
 scalar_t__ krb5_get_seq_num (struct krb5_ctx*,unsigned char*,unsigned char*,int*,scalar_t__*) ; 
 int /*<<< orphan*/  krb5_rc4_setup_enc_key (struct krb5_ctx*,struct crypto_blkcipher*,scalar_t__) ; 
 scalar_t__ make_checksum (struct krb5_ctx*,unsigned char*,int,struct xdr_buf*,int,unsigned char*,int /*<<< orphan*/ ,struct xdr_netobj*) ; 
 scalar_t__ memcmp (char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memmove (void*,void*,int) ; 

__attribute__((used)) static u32
gss_unwrap_kerberos_v1(struct krb5_ctx *kctx, int offset, struct xdr_buf *buf)
{
	int			signalg;
	int			sealalg;
	char			cksumdata[GSS_KRB5_MAX_CKSUM_LEN];
	struct xdr_netobj	md5cksum = {.len = sizeof(cksumdata),
					    .data = cksumdata};
	s32			now;
	int			direction;
	s32			seqnum;
	unsigned char		*ptr;
	int			bodysize;
	void			*data_start, *orig_start;
	int			data_len;
	int			blocksize;
	u32			conflen = kctx->gk5e->conflen;
	int			crypt_offset;
	u8			*cksumkey;

	dprintk("RPC:       gss_unwrap_kerberos\n");

	ptr = (u8 *)buf->head[0].iov_base + offset;
	if (g_verify_token_header(&kctx->mech_used, &bodysize, &ptr,
					buf->len - offset))
		return GSS_S_DEFECTIVE_TOKEN;

	if ((ptr[0] != ((KG_TOK_WRAP_MSG >> 8) & 0xff)) ||
	    (ptr[1] !=  (KG_TOK_WRAP_MSG & 0xff)))
		return GSS_S_DEFECTIVE_TOKEN;

	/* XXX sanity-check bodysize?? */

	/* get the sign and seal algorithms */

	signalg = ptr[2] + (ptr[3] << 8);
	if (signalg != kctx->gk5e->signalg)
		return GSS_S_DEFECTIVE_TOKEN;

	sealalg = ptr[4] + (ptr[5] << 8);
	if (sealalg != kctx->gk5e->sealalg)
		return GSS_S_DEFECTIVE_TOKEN;

	if ((ptr[6] != 0xff) || (ptr[7] != 0xff))
		return GSS_S_DEFECTIVE_TOKEN;

	/*
	 * Data starts after token header and checksum.  ptr points
	 * to the beginning of the token header
	 */
	crypt_offset = ptr + (GSS_KRB5_TOK_HDR_LEN + kctx->gk5e->cksumlength) -
					(unsigned char *)buf->head[0].iov_base;

	/*
	 * Need plaintext seqnum to derive encryption key for arcfour-hmac
	 */
	if (krb5_get_seq_num(kctx, ptr + GSS_KRB5_TOK_HDR_LEN,
			     ptr + 8, &direction, &seqnum))
		return GSS_S_BAD_SIG;

	if ((kctx->initiate && direction != 0xff) ||
	    (!kctx->initiate && direction != 0))
		return GSS_S_BAD_SIG;

	if (kctx->enctype == ENCTYPE_ARCFOUR_HMAC) {
		struct crypto_blkcipher *cipher;
		int err;

		cipher = crypto_alloc_blkcipher(kctx->gk5e->encrypt_name, 0,
						CRYPTO_ALG_ASYNC);
		if (IS_ERR(cipher))
			return GSS_S_FAILURE;

		krb5_rc4_setup_enc_key(kctx, cipher, seqnum);

		err = gss_decrypt_xdr_buf(cipher, buf, crypt_offset);
		crypto_free_blkcipher(cipher);
		if (err)
			return GSS_S_DEFECTIVE_TOKEN;
	} else {
		if (gss_decrypt_xdr_buf(kctx->enc, buf, crypt_offset))
			return GSS_S_DEFECTIVE_TOKEN;
	}

	if (kctx->gk5e->keyed_cksum)
		cksumkey = kctx->cksum;
	else
		cksumkey = NULL;

	if (make_checksum(kctx, ptr, 8, buf, crypt_offset,
					cksumkey, KG_USAGE_SEAL, &md5cksum))
		return GSS_S_FAILURE;

	if (memcmp(md5cksum.data, ptr + GSS_KRB5_TOK_HDR_LEN,
						kctx->gk5e->cksumlength))
		return GSS_S_BAD_SIG;

	/* it got through unscathed.  Make sure the context is unexpired */

	now = get_seconds();

	if (now > kctx->endtime)
		return GSS_S_CONTEXT_EXPIRED;

	/* do sequencing checks */

	/* Copy the data back to the right position.  XXX: Would probably be
	 * better to copy and encrypt at the same time. */

	blocksize = crypto_blkcipher_blocksize(kctx->enc);
	data_start = ptr + (GSS_KRB5_TOK_HDR_LEN + kctx->gk5e->cksumlength) +
					conflen;
	orig_start = buf->head[0].iov_base + offset;
	data_len = (buf->head[0].iov_base + buf->head[0].iov_len) - data_start;
	memmove(orig_start, data_start, data_len);
	buf->head[0].iov_len -= (data_start - orig_start);
	buf->len -= (data_start - orig_start);

	if (gss_krb5_remove_padding(buf, blocksize))
		return GSS_S_DEFECTIVE_TOKEN;

	return GSS_S_COMPLETE;
}