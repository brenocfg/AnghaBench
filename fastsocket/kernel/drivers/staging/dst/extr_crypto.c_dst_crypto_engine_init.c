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
struct dst_crypto_ctl {scalar_t__* cipher_algo; scalar_t__* hash_algo; } ;
struct dst_node {int /*<<< orphan*/  cipher_key; int /*<<< orphan*/  hash_key; int /*<<< orphan*/  max_pages; struct dst_crypto_ctl crypto; } ;
struct dst_crypto_engine {int /*<<< orphan*/  data; int /*<<< orphan*/ * hash; int /*<<< orphan*/ * cipher; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_free_hash (int /*<<< orphan*/ *) ; 
 int dst_crypto_pages_alloc (struct dst_crypto_engine*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_crypto_pages_free (struct dst_crypto_engine*) ; 
 int /*<<< orphan*/ * dst_init_cipher (struct dst_crypto_ctl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dst_init_hash (struct dst_crypto_ctl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dst_crypto_engine_init(struct dst_crypto_engine *e, struct dst_node *n)
{
	int err;
	struct dst_crypto_ctl *ctl = &n->crypto;

	err = dst_crypto_pages_alloc(e, n->max_pages);
	if (err)
		goto err_out_exit;

	e->size = PAGE_SIZE;
	e->data = kmalloc(e->size, GFP_KERNEL);
	if (!e->data) {
		err = -ENOMEM;
		goto err_out_free_pages;
	}

	if (ctl->hash_algo[0]) {
		e->hash = dst_init_hash(ctl, n->hash_key);
		if (IS_ERR(e->hash)) {
			err = PTR_ERR(e->hash);
			e->hash = NULL;
			goto err_out_free;
		}
	}

	if (ctl->cipher_algo[0]) {
		e->cipher = dst_init_cipher(ctl, n->cipher_key);
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
err_out_free_pages:
	dst_crypto_pages_free(e);
err_out_exit:
	return err;
}