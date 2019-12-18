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
struct pohmelfs_crypto_engine {int /*<<< orphan*/  data; scalar_t__ cipher; scalar_t__ hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_ablkcipher (scalar_t__) ; 
 int /*<<< orphan*/  crypto_free_hash (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void pohmelfs_crypto_engine_exit(struct pohmelfs_crypto_engine *e)
{
	if (e->hash)
		crypto_free_hash(e->hash);
	if (e->cipher)
		crypto_free_ablkcipher(e->cipher);
	kfree(e->data);
}