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
struct hifn_request_context {int dummy; } ;
struct hifn_crypto_alg {int /*<<< orphan*/  dev; } ;
struct hifn_context {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int reqsize; } ;
struct crypto_tfm {TYPE_1__ crt_ablkcipher; struct crypto_alg* __crt_alg; } ;
struct crypto_alg {int dummy; } ;

/* Variables and functions */
 struct hifn_crypto_alg* crypto_alg_to_hifn (struct crypto_alg*) ; 
 struct hifn_context* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static int hifn_cra_init(struct crypto_tfm *tfm)
{
	struct crypto_alg *alg = tfm->__crt_alg;
	struct hifn_crypto_alg *ha = crypto_alg_to_hifn(alg);
	struct hifn_context *ctx = crypto_tfm_ctx(tfm);

	ctx->dev = ha->dev;
	tfm->crt_ablkcipher.reqsize = sizeof(struct hifn_request_context);
	return 0;
}