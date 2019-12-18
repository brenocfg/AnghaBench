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
struct crypto_instance {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_drop_skcipher (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_instance_ctx (struct crypto_instance*) ; 
 int /*<<< orphan*/  kfree (struct crypto_instance*) ; 

void skcipher_geniv_free(struct crypto_instance *inst)
{
	crypto_drop_skcipher(crypto_instance_ctx(inst));
	kfree(inst);
}