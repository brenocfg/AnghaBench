#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct crypto_template {int /*<<< orphan*/  instances; int /*<<< orphan*/  module; } ;
struct crypto_larval {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  cra_module; } ;
struct crypto_instance {struct crypto_template* tmpl; int /*<<< orphan*/  list; TYPE_1__ alg; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct crypto_larval*) ; 
 int PTR_ERR (struct crypto_larval*) ; 
 struct crypto_larval* __crypto_register_alg (TYPE_1__*) ; 
 int /*<<< orphan*/  crypto_alg_sem ; 
 int crypto_check_alg (TYPE_1__*) ; 
 int /*<<< orphan*/  crypto_wait_for_test (struct crypto_larval*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int crypto_register_instance(struct crypto_template *tmpl,
			     struct crypto_instance *inst)
{
	struct crypto_larval *larval;
	int err;

	err = crypto_check_alg(&inst->alg);
	if (err)
		goto err;

	inst->alg.cra_module = tmpl->module;

	down_write(&crypto_alg_sem);

	larval = __crypto_register_alg(&inst->alg);
	if (IS_ERR(larval))
		goto unlock;

	hlist_add_head(&inst->list, &tmpl->instances);
	inst->tmpl = tmpl;

unlock:
	up_write(&crypto_alg_sem);

	err = PTR_ERR(larval);
	if (IS_ERR(larval))
		goto err;

	crypto_wait_for_test(larval);
	err = 0;

err:
	return err;
}