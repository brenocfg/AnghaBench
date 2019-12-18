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
struct prng_context {int dummy; } ;
struct crypto_rng {int dummy; } ;

/* Variables and functions */
 struct prng_context* crypto_rng_ctx (struct crypto_rng*) ; 
 int get_prng_bytes (int /*<<< orphan*/ *,unsigned int,struct prng_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cprng_get_random(struct crypto_rng *tfm, u8 *rdata,
			    unsigned int dlen)
{
	struct prng_context *prng = crypto_rng_ctx(tfm);

	return get_prng_bytes(rdata, dlen, prng, 0);
}