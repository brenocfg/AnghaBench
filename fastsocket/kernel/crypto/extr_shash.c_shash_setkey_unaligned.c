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
struct shash_alg {int (* setkey ) (struct crypto_shash*,int /*<<< orphan*/ *,unsigned int) ;} ;
struct crypto_shash {int dummy; } ;

/* Variables and functions */
 scalar_t__ ALIGN (unsigned long,unsigned long) ; 
 int CRYPTO_MINALIGN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct shash_alg* crypto_shash_alg (struct crypto_shash*) ; 
 unsigned long crypto_shash_alignmask (struct crypto_shash*) ; 
 int /*<<< orphan*/ * kmalloc (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 int stub1 (struct crypto_shash*,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int shash_setkey_unaligned(struct crypto_shash *tfm, const u8 *key,
				  unsigned int keylen)
{
	struct shash_alg *shash = crypto_shash_alg(tfm);
	unsigned long alignmask = crypto_shash_alignmask(tfm);
	unsigned long absize;
	u8 *buffer, *alignbuffer;
	int err;

	absize = keylen + (alignmask & ~(CRYPTO_MINALIGN - 1));
	buffer = kmalloc(absize, GFP_KERNEL);
	if (!buffer)
		return -ENOMEM;

	alignbuffer = (u8 *)ALIGN((unsigned long)buffer, alignmask + 1);
	memcpy(alignbuffer, key, keylen);
	err = shash->setkey(tfm, alignbuffer, keylen);
	kzfree(buffer);
	return err;
}