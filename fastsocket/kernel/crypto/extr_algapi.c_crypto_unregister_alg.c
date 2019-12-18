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
struct crypto_alg {int /*<<< orphan*/  (* cra_destroy ) (struct crypto_alg*) ;int /*<<< orphan*/  cra_refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_alg_sem ; 
 int crypto_remove_alg (struct crypto_alg*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_remove_final (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list ; 
 int /*<<< orphan*/  stub1 (struct crypto_alg*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int crypto_unregister_alg(struct crypto_alg *alg)
{
	int ret;
	LIST_HEAD(list);
	
	down_write(&crypto_alg_sem);
	ret = crypto_remove_alg(alg, &list);
	up_write(&crypto_alg_sem);

	if (ret)
		return ret;

	BUG_ON(atomic_read(&alg->cra_refcnt) != 1);
	if (alg->cra_destroy)
		alg->cra_destroy(alg);

	crypto_remove_final(&list);
	return 0;
}