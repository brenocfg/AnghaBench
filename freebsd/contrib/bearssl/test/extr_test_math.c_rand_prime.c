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
typedef  int /*<<< orphan*/  mpz_t ;

/* Variables and functions */
 int /*<<< orphan*/  RNG ; 
 int /*<<< orphan*/  mpz_add_ui (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mpz_divisible_ui_p (int /*<<< orphan*/ ,int) ; 
 scalar_t__ mpz_probab_prime_p (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpz_setbit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpz_sub_ui (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpz_urandomb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
rand_prime(mpz_t x, int size)
{
	for (;;) {
		mpz_urandomb(x, RNG, size - 1);
		mpz_setbit(x, 0);
		mpz_setbit(x, size - 1);
		if (mpz_probab_prime_p(x, 50)) {
			mpz_sub_ui(x, x, 1);
			if (mpz_divisible_ui_p(x, 65537)) {
				continue;
			}
			mpz_add_ui(x, x, 1);
			return;
		}
	}
}