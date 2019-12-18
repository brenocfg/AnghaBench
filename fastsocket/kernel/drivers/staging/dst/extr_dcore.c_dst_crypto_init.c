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
struct dst_node {scalar_t__ trans_cache; } ;
struct dst_ctl {int dummy; } ;
struct dst_crypto_ctl {int hash_keysize; int cipher_keysize; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENODEV ; 
 int dst_node_crypto_init (struct dst_node*,struct dst_crypto_ctl*) ; 

__attribute__((used)) static int dst_crypto_init(struct dst_node *n, struct dst_ctl *ctl,
		void *data, unsigned int size)
{
	struct dst_crypto_ctl *crypto = data;

	if (!n)
		return -ENODEV;

	if (size != sizeof(struct dst_crypto_ctl) + crypto->hash_keysize +
			crypto->cipher_keysize)
		return -EINVAL;

	if (n->trans_cache)
		return -EEXIST;

	return dst_node_crypto_init(n, crypto);
}