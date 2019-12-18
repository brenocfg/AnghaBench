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
struct shash_alg {int (* final ) (struct shash_desc*,int /*<<< orphan*/ *) ;} ;
struct crypto_shash {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * PTR_ALIGN (int /*<<< orphan*/ *,unsigned long) ; 
 struct shash_alg* crypto_shash_alg (struct crypto_shash*) ; 
 unsigned long crypto_shash_alignmask (struct crypto_shash*) ; 
 unsigned int crypto_shash_digestsize (struct crypto_shash*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int shash_align_buffer_size (unsigned int,unsigned long) ; 
 int stub1 (struct shash_desc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int shash_final_unaligned(struct shash_desc *desc, u8 *out)
{
	struct crypto_shash *tfm = desc->tfm;
	unsigned long alignmask = crypto_shash_alignmask(tfm);
	struct shash_alg *shash = crypto_shash_alg(tfm);
	unsigned int ds = crypto_shash_digestsize(tfm);
	u8 ubuf[shash_align_buffer_size(ds, alignmask)]
		__attribute__ ((aligned));
	u8 *buf = PTR_ALIGN(&ubuf[0], alignmask + 1);
	int err;

	err = shash->final(desc, buf);
	if (err)
		goto out;

	memcpy(out, buf, ds);

out:
	memset(buf, 0, ds);
	return err;
}