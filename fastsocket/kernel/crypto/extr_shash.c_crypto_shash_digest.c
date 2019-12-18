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
struct shash_desc {struct crypto_shash* tfm; } ;
struct shash_alg {int (* digest ) (struct shash_desc*,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *) ;} ;
struct crypto_shash {int dummy; } ;

/* Variables and functions */
 struct shash_alg* crypto_shash_alg (struct crypto_shash*) ; 
 unsigned long crypto_shash_alignmask (struct crypto_shash*) ; 
 int shash_digest_unaligned (struct shash_desc*,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *) ; 
 int stub1 (struct shash_desc*,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *) ; 

int crypto_shash_digest(struct shash_desc *desc, const u8 *data,
			unsigned int len, u8 *out)
{
	struct crypto_shash *tfm = desc->tfm;
	struct shash_alg *shash = crypto_shash_alg(tfm);
	unsigned long alignmask = crypto_shash_alignmask(tfm);

	if (((unsigned long)data | (unsigned long)out) & alignmask)
		return shash_digest_unaligned(desc, data, len, out);

	return shash->digest(desc, data, len, out);
}