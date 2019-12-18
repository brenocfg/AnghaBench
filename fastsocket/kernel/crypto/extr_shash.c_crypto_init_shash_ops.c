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
typedef  int u32 ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
#define  CRYPTO_ALG_TYPE_HASH_MASK 128 
 int CRYPTO_ALG_TYPE_MASK ; 
 int EINVAL ; 
 int crypto_init_shash_ops_compat (struct crypto_tfm*) ; 

__attribute__((used)) static int crypto_init_shash_ops(struct crypto_tfm *tfm, u32 type, u32 mask)
{
	switch (mask & CRYPTO_ALG_TYPE_MASK) {
	case CRYPTO_ALG_TYPE_HASH_MASK:
		return crypto_init_shash_ops_compat(tfm);
	}

	return -EINVAL;
}