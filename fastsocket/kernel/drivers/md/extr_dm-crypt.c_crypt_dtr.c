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
struct dm_target {struct crypt_config* private; } ;
struct crypt_config {struct crypt_config* cipher_mode; struct crypt_config* cipher; scalar_t__ dev; scalar_t__ tfm; TYPE_1__* iv_gen_ops; scalar_t__ io_pool; scalar_t__ req_pool; scalar_t__ page_pool; scalar_t__ bs; scalar_t__ crypt_queue; scalar_t__ io_queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dtr ) (struct crypt_config*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (scalar_t__) ; 
 int /*<<< orphan*/  bioset_free (scalar_t__) ; 
 int /*<<< orphan*/  crypto_free_ablkcipher (scalar_t__) ; 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  dm_put_device (struct dm_target*,scalar_t__) ; 
 int /*<<< orphan*/  kzfree (struct crypt_config*) ; 
 int /*<<< orphan*/  mempool_destroy (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct crypt_config*) ; 

__attribute__((used)) static void crypt_dtr(struct dm_target *ti)
{
	struct crypt_config *cc = ti->private;

	ti->private = NULL;

	if (!cc)
		return;

	if (cc->io_queue)
		destroy_workqueue(cc->io_queue);
	if (cc->crypt_queue)
		destroy_workqueue(cc->crypt_queue);

	if (cc->bs)
		bioset_free(cc->bs);

	if (cc->page_pool)
		mempool_destroy(cc->page_pool);
	if (cc->req_pool)
		mempool_destroy(cc->req_pool);
	if (cc->io_pool)
		mempool_destroy(cc->io_pool);

	if (cc->iv_gen_ops && cc->iv_gen_ops->dtr)
		cc->iv_gen_ops->dtr(cc);

	if (cc->tfm && !IS_ERR(cc->tfm))
		crypto_free_ablkcipher(cc->tfm);

	if (cc->dev)
		dm_put_device(ti, cc->dev);

	kzfree(cc->cipher);
	kzfree(cc->cipher_mode);

	/* Must zero key material before freeing */
	kzfree(cc);
}