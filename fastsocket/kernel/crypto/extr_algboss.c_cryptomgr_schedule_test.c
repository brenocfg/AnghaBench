#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct task_struct {int dummy; } ;
struct crypto_test_param {int type; int /*<<< orphan*/  alg; int /*<<< orphan*/  driver; } ;
struct TYPE_6__ {scalar_t__ ivsize; } ;
struct TYPE_5__ {scalar_t__ ivsize; } ;
struct TYPE_4__ {scalar_t__ ivsize; } ;
struct crypto_alg {int cra_flags; TYPE_3__ cra_aead; int /*<<< orphan*/ * cra_type; TYPE_2__ cra_ablkcipher; TYPE_1__ cra_blkcipher; int /*<<< orphan*/  cra_name; int /*<<< orphan*/  cra_driver_name; } ;

/* Variables and functions */
 int CRYPTO_ALG_GENIV ; 
 int CRYPTO_ALG_TESTED ; 
 int CRYPTO_ALG_TYPE_AEAD ; 
 int CRYPTO_ALG_TYPE_BLKCIPHER ; 
 int CRYPTO_ALG_TYPE_BLKCIPHER_MASK ; 
 int CRYPTO_ALG_TYPE_MASK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int NOTIFY_OK ; 
 int NOTIFY_STOP ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  crypto_nivaead_type ; 
 int /*<<< orphan*/  cryptomgr_test ; 
 int /*<<< orphan*/  kfree (struct crypto_test_param*) ; 
 struct task_struct* kthread_run (int /*<<< orphan*/ ,struct crypto_test_param*,char*) ; 
 struct crypto_test_param* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cryptomgr_schedule_test(struct crypto_alg *alg)
{
	struct task_struct *thread;
	struct crypto_test_param *param;
	u32 type;

	if (!try_module_get(THIS_MODULE))
		goto err;

	param = kzalloc(sizeof(*param), GFP_KERNEL);
	if (!param)
		goto err_put_module;

	memcpy(param->driver, alg->cra_driver_name, sizeof(param->driver));
	memcpy(param->alg, alg->cra_name, sizeof(param->alg));
	type = alg->cra_flags;

	/* This piece of crap needs to disappear into per-type test hooks. */
	if ((!((type ^ CRYPTO_ALG_TYPE_BLKCIPHER) &
	       CRYPTO_ALG_TYPE_BLKCIPHER_MASK) && !(type & CRYPTO_ALG_GENIV) &&
	     ((alg->cra_flags & CRYPTO_ALG_TYPE_MASK) ==
	      CRYPTO_ALG_TYPE_BLKCIPHER ? alg->cra_blkcipher.ivsize :
					  alg->cra_ablkcipher.ivsize)) ||
	    (!((type ^ CRYPTO_ALG_TYPE_AEAD) & CRYPTO_ALG_TYPE_MASK) &&
	     alg->cra_type == &crypto_nivaead_type && alg->cra_aead.ivsize))
		type |= CRYPTO_ALG_TESTED;

	param->type = type;

	thread = kthread_run(cryptomgr_test, param, "cryptomgr_test");
	if (IS_ERR(thread))
		goto err_free_param;

	return NOTIFY_STOP;

err_free_param:
	kfree(param);
err_put_module:
	module_put(THIS_MODULE);
err:
	return NOTIFY_OK;
}