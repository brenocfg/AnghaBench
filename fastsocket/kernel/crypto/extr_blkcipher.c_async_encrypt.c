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
struct crypto_tfm {TYPE_1__* __crt_alg; } ;
struct blkcipher_desc {int /*<<< orphan*/  flags; int /*<<< orphan*/  info; int /*<<< orphan*/  tfm; } ;
struct blkcipher_alg {int (* encrypt ) (struct blkcipher_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  flags; struct crypto_tfm* tfm; } ;
struct ablkcipher_request {int /*<<< orphan*/  nbytes; int /*<<< orphan*/  src; int /*<<< orphan*/  dst; TYPE_2__ base; int /*<<< orphan*/  info; } ;
struct TYPE_3__ {struct blkcipher_alg cra_blkcipher; } ;

/* Variables and functions */
 int /*<<< orphan*/  __crypto_blkcipher_cast (struct crypto_tfm*) ; 
 int stub1 (struct blkcipher_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int async_encrypt(struct ablkcipher_request *req)
{
	struct crypto_tfm *tfm = req->base.tfm;
	struct blkcipher_alg *alg = &tfm->__crt_alg->cra_blkcipher;
	struct blkcipher_desc desc = {
		.tfm = __crypto_blkcipher_cast(tfm),
		.info = req->info,
		.flags = req->base.flags,
	};


	return alg->encrypt(&desc, req->dst, req->src, req->nbytes);
}