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
typedef  int u32 ;
struct crypto_test_param {int type; int /*<<< orphan*/  driver; int /*<<< orphan*/  alg; } ;

/* Variables and functions */
 int CRYPTO_ALG_TESTED ; 
 int alg_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  crypto_alg_tested (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct crypto_test_param*) ; 
 int /*<<< orphan*/  module_put_and_exit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cryptomgr_test(void *data)
{
	struct crypto_test_param *param = data;
	u32 type = param->type;
	int err = 0;

	if (type & CRYPTO_ALG_TESTED)
		goto skiptest;

	err = alg_test(param->driver, param->alg, type, CRYPTO_ALG_TESTED);

skiptest:
	crypto_alg_tested(param->driver, err);

	kfree(param);
	module_put_and_exit(0);
}