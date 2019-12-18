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
struct list_head {int dummy; } ;
struct crypto_alg {int /*<<< orphan*/  cra_list; int /*<<< orphan*/  cra_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_DEAD ; 
 int /*<<< orphan*/  CRYPTO_MSG_ALG_UNREGISTER ; 
 int ENOENT ; 
 int /*<<< orphan*/  crypto_notify (int /*<<< orphan*/ ,struct crypto_alg*) ; 
 int /*<<< orphan*/  crypto_remove_spawns (struct crypto_alg*,struct list_head*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int crypto_remove_alg(struct crypto_alg *alg, struct list_head *list)
{
	if (unlikely(list_empty(&alg->cra_list)))
		return -ENOENT;

	alg->cra_flags |= CRYPTO_ALG_DEAD;

	crypto_notify(CRYPTO_MSG_ALG_UNREGISTER, alg);
	list_del_init(&alg->cra_list);
	crypto_remove_spawns(alg, list, NULL);

	return 0;
}