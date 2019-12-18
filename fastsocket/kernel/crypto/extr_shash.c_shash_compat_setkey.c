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
struct shash_desc {int /*<<< orphan*/  tfm; } ;
struct crypto_hash {int dummy; } ;

/* Variables and functions */
 struct shash_desc** crypto_hash_ctx (struct crypto_hash*) ; 
 int crypto_shash_setkey (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int shash_compat_setkey(struct crypto_hash *tfm, const u8 *key,
			       unsigned int keylen)
{
	struct shash_desc **descp = crypto_hash_ctx(tfm);
	struct shash_desc *desc = *descp;

	return crypto_shash_setkey(desc->tfm, key, keylen);
}