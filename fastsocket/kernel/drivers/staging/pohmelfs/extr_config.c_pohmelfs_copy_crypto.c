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
struct pohmelfs_sb {void* hash_string; void* cipher_string; void* hash_key; scalar_t__ cipher_keysize; void* cipher_key; scalar_t__ hash_keysize; int /*<<< orphan*/  cipher_strlen; int /*<<< orphan*/  hash_strlen; int /*<<< orphan*/  idx; } ;
struct pohmelfs_config_group {scalar_t__ cipher_keysize; int /*<<< orphan*/  cipher_key; scalar_t__ hash_keysize; int /*<<< orphan*/  hash_key; int /*<<< orphan*/  cipher_strlen; scalar_t__ cipher_string; int /*<<< orphan*/  hash_strlen; scalar_t__ hash_string; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 void* kstrdup (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pohmelfs_config_lock ; 
 struct pohmelfs_config_group* pohmelfs_find_config_group (int /*<<< orphan*/ ) ; 

int pohmelfs_copy_crypto(struct pohmelfs_sb *psb)
{
	struct pohmelfs_config_group *g;
	int err = -ENOENT;

	mutex_lock(&pohmelfs_config_lock);
	g = pohmelfs_find_config_group(psb->idx);
	if (!g)
		goto err_out_exit;

	if (g->hash_string) {
		err = -ENOMEM;
		psb->hash_string = kstrdup(g->hash_string, GFP_KERNEL);
		if (!psb->hash_string)
			goto err_out_exit;
		psb->hash_strlen = g->hash_strlen;
	}

	if (g->cipher_string) {
		psb->cipher_string = kstrdup(g->cipher_string, GFP_KERNEL);
		if (!psb->cipher_string)
			goto err_out_free_hash_string;
		psb->cipher_strlen = g->cipher_strlen;
	}

	if (g->hash_keysize) {
		psb->hash_key = kmalloc(g->hash_keysize, GFP_KERNEL);
		if (!psb->hash_key)
			goto err_out_free_cipher_string;
		memcpy(psb->hash_key, g->hash_key, g->hash_keysize);
		psb->hash_keysize = g->hash_keysize;
	}

	if (g->cipher_keysize) {
		psb->cipher_key = kmalloc(g->cipher_keysize, GFP_KERNEL);
		if (!psb->cipher_key)
			goto err_out_free_hash;
		memcpy(psb->cipher_key, g->cipher_key, g->cipher_keysize);
		psb->cipher_keysize = g->cipher_keysize;
	}

	mutex_unlock(&pohmelfs_config_lock);

	return 0;

err_out_free_hash:
	kfree(psb->hash_key);
err_out_free_cipher_string:
	kfree(psb->cipher_string);
err_out_free_hash_string:
	kfree(psb->hash_string);
err_out_exit:
	mutex_unlock(&pohmelfs_config_lock);
	return err;
}