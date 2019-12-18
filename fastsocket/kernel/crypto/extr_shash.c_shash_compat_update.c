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
struct shash_desc {int dummy; } ;
struct scatterlist {int dummy; } ;
struct hash_desc {int /*<<< orphan*/  tfm; } ;
struct crypto_hash_walk {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 struct shash_desc** crypto_hash_ctx (int /*<<< orphan*/ ) ; 
 int crypto_hash_walk_done (struct crypto_hash_walk*,int) ; 
 int crypto_hash_walk_first_compat (struct hash_desc*,struct crypto_hash_walk*,struct scatterlist*,unsigned int) ; 
 int crypto_shash_update (struct shash_desc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int shash_compat_update(struct hash_desc *hdesc, struct scatterlist *sg,
			       unsigned int len)
{
	struct shash_desc **descp = crypto_hash_ctx(hdesc->tfm);
	struct shash_desc *desc = *descp;
	struct crypto_hash_walk walk;
	int nbytes;

	for (nbytes = crypto_hash_walk_first_compat(hdesc, &walk, sg, len);
	     nbytes > 0; nbytes = crypto_hash_walk_done(&walk, nbytes))
		nbytes = crypto_shash_update(desc, walk.data, nbytes);

	return nbytes;
}