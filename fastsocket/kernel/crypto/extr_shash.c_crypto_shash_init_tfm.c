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
struct crypto_tfm {int dummy; } ;
struct crypto_shash {int /*<<< orphan*/  descsize; } ;
struct TYPE_2__ {int /*<<< orphan*/  descsize; } ;

/* Variables and functions */
 struct crypto_shash* __crypto_shash_cast (struct crypto_tfm*) ; 
 TYPE_1__* crypto_shash_alg (struct crypto_shash*) ; 

__attribute__((used)) static int crypto_shash_init_tfm(struct crypto_tfm *tfm)
{
	struct crypto_shash *hash = __crypto_shash_cast(tfm);

	hash->descsize = crypto_shash_alg(hash)->descsize;
	return 0;
}