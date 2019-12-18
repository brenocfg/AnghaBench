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
struct crypto_rng {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int krng_get_random(struct crypto_rng *tfm, u8 *rdata, unsigned int dlen)
{
	get_random_bytes(rdata, dlen);
	return 0;
}