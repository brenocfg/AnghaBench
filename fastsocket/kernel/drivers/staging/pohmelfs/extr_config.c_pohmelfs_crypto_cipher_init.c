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
typedef  int /*<<< orphan*/  u8 ;
struct pohmelfs_crypto {int strlen; int /*<<< orphan*/  keysize; scalar_t__ data; } ;
struct pohmelfs_config_group {int cipher_strlen; int /*<<< orphan*/  cipher_key; scalar_t__ cipher_string; int /*<<< orphan*/  cipher_keysize; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kstrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pohmelfs_crypto_cipher_init(struct pohmelfs_config_group *g, struct pohmelfs_crypto *c)
{
	char *algo = (char *)c->data;
	u8 *key = (u8 *)(algo + c->strlen);

	if (g->cipher_string)
		return -EEXIST;

	g->cipher_string = kstrdup(algo, GFP_KERNEL);
	if (!g->cipher_string)
		return -ENOMEM;
	g->cipher_strlen = c->strlen;
	g->cipher_keysize = c->keysize;

	g->cipher_key = kmalloc(c->keysize, GFP_KERNEL);
	if (!g->cipher_key) {
		kfree(g->cipher_string);
		return -ENOMEM;
	}

	memcpy(g->cipher_key, key, c->keysize);

	return 0;
}