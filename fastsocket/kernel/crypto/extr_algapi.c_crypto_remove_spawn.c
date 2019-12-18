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
struct list_head {int dummy; } ;
struct crypto_template {int dummy; } ;
struct crypto_spawn {struct crypto_instance* inst; } ;
struct TYPE_3__ {int /*<<< orphan*/  cra_users; int /*<<< orphan*/  cra_destroy; int /*<<< orphan*/  cra_list; int /*<<< orphan*/  cra_flags; } ;
struct crypto_instance {TYPE_1__ alg; int /*<<< orphan*/  list; struct crypto_template* tmpl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CRYPTO_ALG_DEAD ; 
 int /*<<< orphan*/  CRYPTO_MSG_ALG_UNREGISTER ; 
 int /*<<< orphan*/  crypto_destroy_instance ; 
 scalar_t__ crypto_is_dead (TYPE_1__*) ; 
 int /*<<< orphan*/  crypto_notify (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  crypto_tmpl_get (struct crypto_template*) ; 
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 scalar_t__ hlist_unhashed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,struct list_head*) ; 

__attribute__((used)) static void crypto_remove_spawn(struct crypto_spawn *spawn,
				struct list_head *list)
{
	struct crypto_instance *inst = spawn->inst;
	struct crypto_template *tmpl = inst->tmpl;

	if (crypto_is_dead(&inst->alg))
		return;

	inst->alg.cra_flags |= CRYPTO_ALG_DEAD;
	if (hlist_unhashed(&inst->list))
		return;

	if (!tmpl || !crypto_tmpl_get(tmpl))
		return;

	crypto_notify(CRYPTO_MSG_ALG_UNREGISTER, &inst->alg);
	list_move(&inst->alg.cra_list, list);
	hlist_del(&inst->list);
	inst->alg.cra_destroy = crypto_destroy_instance;

	BUG_ON(!list_empty(&inst->alg.cra_users));
}