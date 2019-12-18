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
struct TYPE_3__ {int /*<<< orphan*/  ivsize; int /*<<< orphan*/  givencrypt; } ;
struct TYPE_4__ {TYPE_1__ cra_aead; int /*<<< orphan*/  cra_ctxsize; int /*<<< orphan*/  cra_exit; int /*<<< orphan*/  cra_init; } ;
struct crypto_instance {TYPE_2__ alg; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct crypto_instance*) ; 
 struct crypto_instance* aead_geniv_alloc (int /*<<< orphan*/ *,struct rtattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aead_geniv_exit ; 
 int /*<<< orphan*/  seqiv_aead_givencrypt_first ; 
 int /*<<< orphan*/  seqiv_aead_init ; 
 int /*<<< orphan*/  seqiv_tmpl ; 

__attribute__((used)) static struct crypto_instance *seqiv_aead_alloc(struct rtattr **tb)
{
	struct crypto_instance *inst;

	inst = aead_geniv_alloc(&seqiv_tmpl, tb, 0, 0);

	if (IS_ERR(inst))
		goto out;

	inst->alg.cra_aead.givencrypt = seqiv_aead_givencrypt_first;

	inst->alg.cra_init = seqiv_aead_init;
	inst->alg.cra_exit = aead_geniv_exit;

	inst->alg.cra_ctxsize = inst->alg.cra_aead.ivsize;

out:
	return inst;
}