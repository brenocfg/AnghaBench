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
struct scatterlist {int /*<<< orphan*/  length; } ;
struct hash_desc {int /*<<< orphan*/  tfm; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_ASYNC ; 
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_alloc_hash (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_hash (int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_hash_digest (struct hash_desc*,struct scatterlist*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_hash_digestsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md5_to_hex (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_ok ; 
 int /*<<< orphan*/  nfserr_resource ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__be32
nfs4_make_rec_clidname(char *dname, struct xdr_netobj *clname)
{
	struct xdr_netobj cksum;
	struct hash_desc desc;
	struct scatterlist sg;
	__be32 status = nfserr_resource;

	dprintk("NFSD: nfs4_make_rec_clidname for %.*s\n",
			clname->len, clname->data);
	desc.flags = CRYPTO_TFM_REQ_MAY_SLEEP;
	desc.tfm = crypto_alloc_hash("md5", 0, CRYPTO_ALG_ASYNC);
	if (IS_ERR(desc.tfm))
		goto out_no_tfm;
	cksum.len = crypto_hash_digestsize(desc.tfm);
	cksum.data = kmalloc(cksum.len, GFP_KERNEL);
	if (cksum.data == NULL)
 		goto out;

	sg_init_one(&sg, clname->data, clname->len);

	if (crypto_hash_digest(&desc, &sg, sg.length, cksum.data))
		goto out;

	md5_to_hex(dname, cksum.data);

	status = nfs_ok;
out:
	kfree(cksum.data);
	crypto_free_hash(desc.tfm);
out_no_tfm:
	return status;
}