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
struct hash_desc {scalar_t__ flags; int /*<<< orphan*/  tfm; } ;
struct dst_crypto_engine {int /*<<< orphan*/  hash; struct hash_desc* data; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int crypto_hash_final (struct hash_desc*,void*) ; 
 int crypto_hash_init (struct hash_desc*) ; 
 int /*<<< orphan*/  dst_hash_iterator ; 
 int dst_trans_iter_in (struct bio*,struct dst_crypto_engine*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dst_hash(struct dst_crypto_engine *e, struct bio *bio, void *dst)
{
	struct hash_desc *desc = e->data;
	int err;

	desc->tfm = e->hash;
	desc->flags = 0;

	err = crypto_hash_init(desc);
	if (err)
		return err;

	err = dst_trans_iter_in(bio, e, dst_hash_iterator);
	if (err)
		return err;

	err = crypto_hash_final(desc, dst);
	if (err)
		return err;

	return 0;
}