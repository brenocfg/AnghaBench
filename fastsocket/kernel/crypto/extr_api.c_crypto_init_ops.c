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
typedef  int /*<<< orphan*/  u32 ;
struct crypto_type {int (* init ) (struct crypto_tfm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct crypto_tfm {TYPE_1__* __crt_alg; } ;
struct TYPE_2__ {struct crypto_type* cra_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  CRYPTO_ALG_TYPE_CIPHER 129 
#define  CRYPTO_ALG_TYPE_COMPRESS 128 
 int EINVAL ; 
 int crypto_init_cipher_ops (struct crypto_tfm*) ; 
 int crypto_init_compress_ops (struct crypto_tfm*) ; 
 int crypto_tfm_alg_type (struct crypto_tfm*) ; 
 int stub1 (struct crypto_tfm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int crypto_init_ops(struct crypto_tfm *tfm, u32 type, u32 mask)
{
	const struct crypto_type *type_obj = tfm->__crt_alg->cra_type;

	if (type_obj)
		return type_obj->init(tfm, type, mask);

	switch (crypto_tfm_alg_type(tfm)) {
	case CRYPTO_ALG_TYPE_CIPHER:
		return crypto_init_cipher_ops(tfm);

	case CRYPTO_ALG_TYPE_COMPRESS:
		return crypto_init_compress_ops(tfm);
	
	default:
		break;
	}
	
	BUG();
	return -EINVAL;
}