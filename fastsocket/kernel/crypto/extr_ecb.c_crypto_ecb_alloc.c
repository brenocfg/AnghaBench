#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rtattr {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  decrypt; int /*<<< orphan*/  encrypt; int /*<<< orphan*/  setkey; int /*<<< orphan*/  max_keysize; int /*<<< orphan*/  min_keysize; } ;
struct TYPE_6__ {int cra_ctxsize; TYPE_2__ cra_blkcipher; int /*<<< orphan*/  cra_exit; int /*<<< orphan*/  cra_init; int /*<<< orphan*/ * cra_type; int /*<<< orphan*/  cra_alignmask; int /*<<< orphan*/  cra_blocksize; int /*<<< orphan*/  cra_priority; int /*<<< orphan*/  cra_flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  cia_max_keysize; int /*<<< orphan*/  cia_min_keysize; } ;
struct crypto_instance {TYPE_3__ alg; TYPE_1__ cra_cipher; int /*<<< orphan*/  cra_alignmask; int /*<<< orphan*/  cra_blocksize; int /*<<< orphan*/  cra_priority; } ;
struct crypto_ecb_ctx {int dummy; } ;
struct crypto_alg {TYPE_3__ alg; TYPE_1__ cra_cipher; int /*<<< orphan*/  cra_alignmask; int /*<<< orphan*/  cra_blocksize; int /*<<< orphan*/  cra_priority; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_TYPE_BLKCIPHER ; 
 int /*<<< orphan*/  CRYPTO_ALG_TYPE_CIPHER ; 
 int /*<<< orphan*/  CRYPTO_ALG_TYPE_MASK ; 
 struct crypto_instance* ERR_CAST (struct crypto_instance*) ; 
 struct crypto_instance* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct crypto_instance*) ; 
 struct crypto_instance* crypto_alloc_instance (char*,struct crypto_instance*) ; 
 int /*<<< orphan*/  crypto_blkcipher_type ; 
 int crypto_check_attr_type (struct rtattr**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ecb_decrypt ; 
 int /*<<< orphan*/  crypto_ecb_encrypt ; 
 int /*<<< orphan*/  crypto_ecb_exit_tfm ; 
 int /*<<< orphan*/  crypto_ecb_init_tfm ; 
 int /*<<< orphan*/  crypto_ecb_setkey ; 
 struct crypto_instance* crypto_get_attr_alg (struct rtattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_mod_put (struct crypto_instance*) ; 

__attribute__((used)) static struct crypto_instance *crypto_ecb_alloc(struct rtattr **tb)
{
	struct crypto_instance *inst;
	struct crypto_alg *alg;
	int err;

	err = crypto_check_attr_type(tb, CRYPTO_ALG_TYPE_BLKCIPHER);
	if (err)
		return ERR_PTR(err);

	alg = crypto_get_attr_alg(tb, CRYPTO_ALG_TYPE_CIPHER,
				  CRYPTO_ALG_TYPE_MASK);
	if (IS_ERR(alg))
		return ERR_CAST(alg);

	inst = crypto_alloc_instance("ecb", alg);
	if (IS_ERR(inst))
		goto out_put_alg;

	inst->alg.cra_flags = CRYPTO_ALG_TYPE_BLKCIPHER;
	inst->alg.cra_priority = alg->cra_priority;
	inst->alg.cra_blocksize = alg->cra_blocksize;
	inst->alg.cra_alignmask = alg->cra_alignmask;
	inst->alg.cra_type = &crypto_blkcipher_type;

	inst->alg.cra_blkcipher.min_keysize = alg->cra_cipher.cia_min_keysize;
	inst->alg.cra_blkcipher.max_keysize = alg->cra_cipher.cia_max_keysize;

	inst->alg.cra_ctxsize = sizeof(struct crypto_ecb_ctx);

	inst->alg.cra_init = crypto_ecb_init_tfm;
	inst->alg.cra_exit = crypto_ecb_exit_tfm;

	inst->alg.cra_blkcipher.setkey = crypto_ecb_setkey;
	inst->alg.cra_blkcipher.encrypt = crypto_ecb_encrypt;
	inst->alg.cra_blkcipher.decrypt = crypto_ecb_decrypt;

out_put_alg:
	crypto_mod_put(alg);
	return inst;
}