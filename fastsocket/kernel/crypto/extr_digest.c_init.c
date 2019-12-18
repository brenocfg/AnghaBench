#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hash_desc {int /*<<< orphan*/  tfm; } ;
struct crypto_tfm {TYPE_2__* __crt_alg; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* dia_init ) (struct crypto_tfm*) ;} ;
struct TYPE_4__ {TYPE_1__ cra_digest; } ;

/* Variables and functions */
 struct crypto_tfm* crypto_hash_tfm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct crypto_tfm*) ; 

__attribute__((used)) static int init(struct hash_desc *desc)
{
	struct crypto_tfm *tfm = crypto_hash_tfm(desc->tfm);

	tfm->__crt_alg->cra_digest.dia_init(tfm);
	return 0;
}