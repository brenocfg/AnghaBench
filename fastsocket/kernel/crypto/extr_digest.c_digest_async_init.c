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
struct digest_alg {int /*<<< orphan*/  (* dia_init ) (struct crypto_tfm*) ;} ;
struct crypto_tfm {TYPE_2__* __crt_alg; } ;
struct TYPE_3__ {struct crypto_tfm* tfm; } ;
struct ahash_request {TYPE_1__ base; } ;
struct TYPE_4__ {struct digest_alg cra_digest; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct crypto_tfm*) ; 

__attribute__((used)) static int digest_async_init(struct ahash_request *req)
{
	struct crypto_tfm *tfm  = req->base.tfm;
	struct digest_alg *dalg = &tfm->__crt_alg->cra_digest;

	dalg->dia_init(tfm);
	return 0;
}