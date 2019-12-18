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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct xdr_netobj {int len; int /*<<< orphan*/ * data; } ;
struct xdr_buf {scalar_t__ len; } ;
struct krb5_ctx {TYPE_2__* gk5e; int /*<<< orphan*/ * initiator_integ; struct crypto_blkcipher* initiator_enc_aux; struct crypto_blkcipher* initiator_enc; int /*<<< orphan*/ * acceptor_integ; struct crypto_blkcipher* acceptor_enc_aux; struct crypto_blkcipher* acceptor_enc; scalar_t__ initiate; } ;
struct TYPE_3__ {struct crypto_blkcipher* tfm; scalar_t__ flags; int /*<<< orphan*/  info; } ;
struct decryptor_desc {int /*<<< orphan*/  iv; int /*<<< orphan*/  frags; TYPE_1__ desc; scalar_t__ fraglen; scalar_t__ fragno; } ;
struct crypto_blkcipher {int dummy; } ;
typedef  int /*<<< orphan*/  our_hmac ;
struct TYPE_4__ {scalar_t__ cksumlength; scalar_t__ conflen; } ;

/* Variables and functions */
 int GSS_KRB5_MAX_CKSUM_LEN ; 
 scalar_t__ GSS_KRB5_TOK_HDR_LEN ; 
 scalar_t__ GSS_S_BAD_SIG ; 
 scalar_t__ GSS_S_FAILURE ; 
 unsigned int KG_USAGE_ACCEPTOR_SEAL ; 
 unsigned int KG_USAGE_INITIATOR_SEAL ; 
 int crypto_blkcipher_blocksize (struct crypto_blkcipher*) ; 
 int /*<<< orphan*/  decryptor ; 
 scalar_t__ gss_krb5_cts_crypt (struct crypto_blkcipher*,struct xdr_buf*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ make_checksum_v2 (struct krb5_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct xdr_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,struct xdr_netobj*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ read_bytes_from_xdr_buf (struct xdr_buf*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sg_init_table (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xdr_buf_subsegment (struct xdr_buf*,struct xdr_buf*,scalar_t__,scalar_t__) ; 
 scalar_t__ xdr_process_buf (struct xdr_buf*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct decryptor_desc*) ; 

u32
gss_krb5_aes_decrypt(struct krb5_ctx *kctx, u32 offset, struct xdr_buf *buf,
		     u32 *headskip, u32 *tailskip)
{
	struct xdr_buf subbuf;
	u32 ret = 0;
	u8 *cksum_key;
	struct crypto_blkcipher *cipher, *aux_cipher;
	struct xdr_netobj our_hmac_obj;
	u8 our_hmac[GSS_KRB5_MAX_CKSUM_LEN];
	u8 pkt_hmac[GSS_KRB5_MAX_CKSUM_LEN];
	int nblocks, blocksize, cbcbytes;
	struct decryptor_desc desc;
	unsigned int usage;

	if (kctx->initiate) {
		cipher = kctx->acceptor_enc;
		aux_cipher = kctx->acceptor_enc_aux;
		cksum_key = kctx->acceptor_integ;
		usage = KG_USAGE_ACCEPTOR_SEAL;
	} else {
		cipher = kctx->initiator_enc;
		aux_cipher = kctx->initiator_enc_aux;
		cksum_key = kctx->initiator_integ;
		usage = KG_USAGE_INITIATOR_SEAL;
	}
	blocksize = crypto_blkcipher_blocksize(cipher);


	/* create a segment skipping the header and leaving out the checksum */
	xdr_buf_subsegment(buf, &subbuf, offset + GSS_KRB5_TOK_HDR_LEN,
				    (buf->len - offset - GSS_KRB5_TOK_HDR_LEN -
				     kctx->gk5e->cksumlength));

	nblocks = (subbuf.len + blocksize - 1) / blocksize;

	cbcbytes = 0;
	if (nblocks > 2)
		cbcbytes = (nblocks - 2) * blocksize;

	memset(desc.iv, 0, sizeof(desc.iv));

	if (cbcbytes) {
		desc.fragno = 0;
		desc.fraglen = 0;
		desc.desc.info = desc.iv;
		desc.desc.flags = 0;
		desc.desc.tfm = aux_cipher;

		sg_init_table(desc.frags, 4);

		ret = xdr_process_buf(&subbuf, 0, cbcbytes, decryptor, &desc);
		if (ret)
			goto out_err;
	}

	/* Make sure IV carries forward from any CBC results. */
	ret = gss_krb5_cts_crypt(cipher, &subbuf, cbcbytes, desc.iv, NULL, 0);
	if (ret)
		goto out_err;


	/* Calculate our hmac over the plaintext data */
	our_hmac_obj.len = sizeof(our_hmac);
	our_hmac_obj.data = our_hmac;

	ret = make_checksum_v2(kctx, NULL, 0, &subbuf, 0,
			       cksum_key, usage, &our_hmac_obj);
	if (ret)
		goto out_err;

	/* Get the packet's hmac value */
	ret = read_bytes_from_xdr_buf(buf, buf->len - kctx->gk5e->cksumlength,
				      pkt_hmac, kctx->gk5e->cksumlength);
	if (ret)
		goto out_err;

	if (memcmp(pkt_hmac, our_hmac, kctx->gk5e->cksumlength) != 0) {
		ret = GSS_S_BAD_SIG;
		goto out_err;
	}
	*headskip = kctx->gk5e->conflen;
	*tailskip = kctx->gk5e->cksumlength;
out_err:
	if (ret && ret != GSS_S_BAD_SIG)
		ret = GSS_S_FAILURE;
	return ret;
}