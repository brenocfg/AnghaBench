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
struct pohmelfs_sb {scalar_t__ cipher_string; scalar_t__ hash_string; } ;
struct pohmelfs_crypto_engine {int /*<<< orphan*/  data; int /*<<< orphan*/ * hash; int /*<<< orphan*/ * cipher; int /*<<< orphan*/  size; scalar_t__ page_num; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_free_hash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pohmelfs_init_cipher (struct pohmelfs_sb*) ; 
 int /*<<< orphan*/ * pohmelfs_init_hash (struct pohmelfs_sb*) ; 

int pohmelfs_crypto_engine_init(struct pohmelfs_crypto_engine *e, struct pohmelfs_sb *psb)
{
	int err;

	e->page_num = 0;

	e->size = PAGE_SIZE;
	e->data = kmalloc(e->size, GFP_KERNEL);
	if (!e->data) {
		err = -ENOMEM;
		goto err_out_exit;
	}

	if (psb->hash_string) {
		e->hash = pohmelfs_init_hash(psb);
		if (IS_ERR(e->hash)) {
			err = PTR_ERR(e->hash);
			e->hash = NULL;
			goto err_out_free;
		}
	}

	if (psb->cipher_string) {
		e->cipher = pohmelfs_init_cipher(psb);
		if (IS_ERR(e->cipher)) {
			err = PTR_ERR(e->cipher);
			e->cipher = NULL;
			goto err_out_free_hash;
		}
	}

	return 0;

err_out_free_hash:
	crypto_free_hash(e->hash);
err_out_free:
	kfree(e->data);
err_out_exit:
	return err;
}