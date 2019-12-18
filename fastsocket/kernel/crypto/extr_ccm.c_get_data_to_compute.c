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
typedef  int /*<<< orphan*/  u8 ;
struct scatterlist {int dummy; } ;
struct scatter_walk {int /*<<< orphan*/  sg; } ;
struct crypto_cipher {int dummy; } ;
struct crypto_ccm_req_priv_ctx {int ilen; int /*<<< orphan*/ * idata; int /*<<< orphan*/ * odata; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  compute_mac (struct crypto_cipher*,int /*<<< orphan*/ *,int,struct crypto_ccm_req_priv_ctx*) ; 
 int /*<<< orphan*/  crypto_cipher_encrypt_one (struct crypto_cipher*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_xor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  crypto_yield (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scatterwalk_advance (struct scatter_walk*,int) ; 
 int scatterwalk_clamp (struct scatter_walk*,unsigned int) ; 
 int /*<<< orphan*/  scatterwalk_done (struct scatter_walk*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/ * scatterwalk_map (struct scatter_walk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scatterwalk_start (struct scatter_walk*,struct scatterlist*) ; 
 int /*<<< orphan*/  scatterwalk_unmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct scatterlist* sg_next (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_data_to_compute(struct crypto_cipher *tfm,
			       struct crypto_ccm_req_priv_ctx *pctx,
			       struct scatterlist *sg, unsigned int len)
{
	struct scatter_walk walk;
	u8 *data_src;
	int n;

	scatterwalk_start(&walk, sg);

	while (len) {
		n = scatterwalk_clamp(&walk, len);
		if (!n) {
			scatterwalk_start(&walk, sg_next(walk.sg));
			n = scatterwalk_clamp(&walk, len);
		}
		data_src = scatterwalk_map(&walk, 0);

		compute_mac(tfm, data_src, n, pctx);
		len -= n;

		scatterwalk_unmap(data_src, 0);
		scatterwalk_advance(&walk, n);
		scatterwalk_done(&walk, 0, len);
		if (len)
			crypto_yield(pctx->flags);
	}

	/* any leftover needs padding and then encrypted */
	if (pctx->ilen) {
		int padlen;
		u8 *odata = pctx->odata;
		u8 *idata = pctx->idata;

		padlen = 16 - pctx->ilen;
		memset(idata + pctx->ilen, 0, padlen);
		crypto_xor(odata, idata, 16);
		crypto_cipher_encrypt_one(tfm, odata, odata);
		pctx->ilen = 0;
	}
}