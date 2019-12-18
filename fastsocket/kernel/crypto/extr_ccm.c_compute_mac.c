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
struct crypto_cipher {int dummy; } ;
struct crypto_ccm_req_priv_ctx {unsigned int ilen; int /*<<< orphan*/ * idata; int /*<<< orphan*/ * odata; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_cipher_encrypt_one (struct crypto_cipher*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_xor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void compute_mac(struct crypto_cipher *tfm, u8 *data, int n,
		       struct crypto_ccm_req_priv_ctx *pctx)
{
	unsigned int bs = 16;
	u8 *odata = pctx->odata;
	u8 *idata = pctx->idata;
	int datalen, getlen;

	datalen = n;

	/* first time in here, block may be partially filled. */
	getlen = bs - pctx->ilen;
	if (datalen >= getlen) {
		memcpy(idata + pctx->ilen, data, getlen);
		crypto_xor(odata, idata, bs);
		crypto_cipher_encrypt_one(tfm, odata, odata);
		datalen -= getlen;
		data += getlen;
		pctx->ilen = 0;
	}

	/* now encrypt rest of data */
	while (datalen >= bs) {
		crypto_xor(odata, data, bs);
		crypto_cipher_encrypt_one(tfm, odata, odata);

		datalen -= bs;
		data += bs;
	}

	/* check and see if there's leftover data that wasn't
	 * enough to fill a block.
	 */
	if (datalen) {
		memcpy(idata + pctx->ilen, data, datalen);
		pctx->ilen += datalen;
	}
}