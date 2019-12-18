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
struct xdr_netobj {int /*<<< orphan*/ * data; int /*<<< orphan*/  len; } ;
struct xdr_buf {scalar_t__ len; } ;
struct scatterlist {int /*<<< orphan*/  length; } ;
struct hash_desc {int /*<<< orphan*/  tfm; int /*<<< orphan*/  flags; } ;
typedef  int s32 ;

/* Variables and functions */
#define  CKSUMTYPE_HMAC_MD5 128 
 int /*<<< orphan*/  CRYPTO_ALG_ASYNC ; 
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int GSS_S_FAILURE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_alloc_hash (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_hash_digestsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_hash_final (struct hash_desc*,int /*<<< orphan*/ *) ; 
 int crypto_hash_init (struct hash_desc*) ; 
 int crypto_hash_setkey (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_hash_update (struct hash_desc*,struct scatterlist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,char*,unsigned int) ; 
 int /*<<< orphan*/  spkm3_checksummer ; 
 int /*<<< orphan*/  xdr_process_buf (struct xdr_buf*,unsigned int,scalar_t__,int /*<<< orphan*/ ,struct hash_desc*) ; 

s32
make_spkm3_checksum(s32 cksumtype, struct xdr_netobj *key, char *header,
		    unsigned int hdrlen, struct xdr_buf *body,
		    unsigned int body_offset, struct xdr_netobj *cksum)
{
	char				*cksumname;
	struct hash_desc		desc; /* XXX add to ctx? */
	struct scatterlist		sg[1];
	int err;

	switch (cksumtype) {
		case CKSUMTYPE_HMAC_MD5:
			cksumname = "hmac(md5)";
			break;
		default:
			dprintk("RPC:       spkm3_make_checksum:"
					" unsupported checksum %d", cksumtype);
			return GSS_S_FAILURE;
	}

	if (key->data == NULL || key->len <= 0) return GSS_S_FAILURE;

	desc.tfm = crypto_alloc_hash(cksumname, 0, CRYPTO_ALG_ASYNC);
	if (IS_ERR(desc.tfm))
		return GSS_S_FAILURE;
	cksum->len = crypto_hash_digestsize(desc.tfm);
	desc.flags = CRYPTO_TFM_REQ_MAY_SLEEP;

	err = crypto_hash_setkey(desc.tfm, key->data, key->len);
	if (err)
		goto out;

	err = crypto_hash_init(&desc);
	if (err)
		goto out;

	sg_init_one(sg, header, hdrlen);
	crypto_hash_update(&desc, sg, sg->length);

	xdr_process_buf(body, body_offset, body->len - body_offset,
			spkm3_checksummer, &desc);
	crypto_hash_final(&desc, cksum->data);

out:
	crypto_free_hash(desc.tfm);

	return err ? GSS_S_FAILURE : 0;
}