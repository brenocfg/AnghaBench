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
struct crypto_skcipher_spawn {int dummy; } ;
struct crypto_instance {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_drop_skcipher (struct crypto_skcipher_spawn*) ; 
 struct crypto_skcipher_spawn* crypto_instance_ctx (struct crypto_instance*) ; 
 int /*<<< orphan*/  kfree (struct crypto_instance*) ; 

__attribute__((used)) static void crypto_rfc3686_free(struct crypto_instance *inst)
{
	struct crypto_skcipher_spawn *spawn = crypto_instance_ctx(inst);

	crypto_drop_skcipher(spawn);
	kfree(inst);
}