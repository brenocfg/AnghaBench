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
struct shash_desc {int dummy; } ;
struct crypto_alg {int dummy; } ;

/* Variables and functions */
#define  CRYPTO_ALG_TYPE_HASH_MASK 128 
 int CRYPTO_ALG_TYPE_MASK ; 

__attribute__((used)) static unsigned int crypto_shash_ctxsize(struct crypto_alg *alg, u32 type,
					 u32 mask)
{
	switch (mask & CRYPTO_ALG_TYPE_MASK) {
	case CRYPTO_ALG_TYPE_HASH_MASK:
		return sizeof(struct shash_desc *);
	}

	return 0;
}