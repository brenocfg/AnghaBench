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
struct s390_aes_ctx {int /*<<< orphan*/  dec; int /*<<< orphan*/  enc; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KMCTR_AES_128_DECRYPT ; 
 int /*<<< orphan*/  KMCTR_AES_128_ENCRYPT ; 
 int /*<<< orphan*/  KMCTR_AES_192_DECRYPT ; 
 int /*<<< orphan*/  KMCTR_AES_192_ENCRYPT ; 
 int /*<<< orphan*/  KMCTR_AES_256_DECRYPT ; 
 int /*<<< orphan*/  KMCTR_AES_256_ENCRYPT ; 
 int aes_set_key (struct crypto_tfm*,int /*<<< orphan*/  const*,unsigned int) ; 
 struct s390_aes_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static int ctr_aes_set_key(struct crypto_tfm *tfm, const u8 *in_key,
			   unsigned int key_len)
{
	struct s390_aes_ctx *sctx = crypto_tfm_ctx(tfm);

	switch (key_len) {
	case 16:
		sctx->enc = KMCTR_AES_128_ENCRYPT;
		sctx->dec = KMCTR_AES_128_DECRYPT;
		break;
	case 24:
		sctx->enc = KMCTR_AES_192_ENCRYPT;
		sctx->dec = KMCTR_AES_192_DECRYPT;
		break;
	case 32:
		sctx->enc = KMCTR_AES_256_ENCRYPT;
		sctx->dec = KMCTR_AES_256_DECRYPT;
		break;
	}

	return aes_set_key(tfm, in_key, key_len);
}