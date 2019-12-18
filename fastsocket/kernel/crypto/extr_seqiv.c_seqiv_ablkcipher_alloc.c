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
struct rtattr {int dummy; } ;
struct TYPE_3__ {scalar_t__ ivsize; int /*<<< orphan*/  givencrypt; } ;
struct TYPE_4__ {TYPE_1__ cra_ablkcipher; int /*<<< orphan*/  cra_ctxsize; int /*<<< orphan*/  cra_exit; int /*<<< orphan*/  cra_init; } ;
struct crypto_instance {TYPE_2__ alg; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct crypto_instance*) ; 
 int /*<<< orphan*/  seqiv_givencrypt_first ; 
 int /*<<< orphan*/  seqiv_init ; 
 int /*<<< orphan*/  seqiv_tmpl ; 
 struct crypto_instance* skcipher_geniv_alloc (int /*<<< orphan*/ *,struct rtattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_geniv_exit ; 

__attribute__((used)) static struct crypto_instance *seqiv_ablkcipher_alloc(struct rtattr **tb)
{
	struct crypto_instance *inst;

	inst = skcipher_geniv_alloc(&seqiv_tmpl, tb, 0, 0);

	if (IS_ERR(inst))
		goto out;

	inst->alg.cra_ablkcipher.givencrypt = seqiv_givencrypt_first;

	inst->alg.cra_init = seqiv_init;
	inst->alg.cra_exit = skcipher_geniv_exit;

	inst->alg.cra_ctxsize += inst->alg.cra_ablkcipher.ivsize;

out:
	return inst;
}