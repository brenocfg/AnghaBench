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
 int /*<<< orphan*/  crypto_put_default_rng () ; 
 int /*<<< orphan*/  skcipher_geniv_free (struct crypto_instance*) ; 

__attribute__((used)) static void eseqiv_free(struct crypto_instance *inst)
{
	skcipher_geniv_free(inst);
	crypto_put_default_rng();
}