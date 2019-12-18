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
struct rtattr {int dummy; } ;
struct crypto_template {int dummy; } ;
struct crypto_attr_type {int type; int mask; } ;

/* Variables and functions */
#define  CRYPTO_ALG_TYPE_AEAD 130 
#define  CRYPTO_ALG_TYPE_BLKCIPHER 129 
#define  CRYPTO_ALG_TYPE_DIGEST 128 
 int CRYPTO_ALG_TYPE_MASK ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct crypto_attr_type*) ; 
 int PTR_ERR (struct crypto_attr_type*) ; 
 int cryptd_create_aead (struct crypto_template*,struct rtattr**,int /*<<< orphan*/ *) ; 
 int cryptd_create_blkcipher (struct crypto_template*,struct rtattr**,int /*<<< orphan*/ *) ; 
 int cryptd_create_hash (struct crypto_template*,struct rtattr**,int /*<<< orphan*/ *) ; 
 struct crypto_attr_type* crypto_get_attr_type (struct rtattr**) ; 
 int /*<<< orphan*/  queue ; 

__attribute__((used)) static int cryptd_create(struct crypto_template *tmpl, struct rtattr **tb)
{
	struct crypto_attr_type *algt;

	algt = crypto_get_attr_type(tb);
	if (IS_ERR(algt))
		return PTR_ERR(algt);

	switch (algt->type & algt->mask & CRYPTO_ALG_TYPE_MASK) {
	case CRYPTO_ALG_TYPE_BLKCIPHER:
		return cryptd_create_blkcipher(tmpl, tb, &queue);
	case CRYPTO_ALG_TYPE_DIGEST:
		return cryptd_create_hash(tmpl, tb, &queue);
	case CRYPTO_ALG_TYPE_AEAD:
		return cryptd_create_aead(tmpl, tb, &queue);
	}

	return -EINVAL;
}