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
struct crypto_rsa_key {int /*<<< orphan*/  iqmp; int /*<<< orphan*/  dmq1; int /*<<< orphan*/  dmp1; int /*<<< orphan*/  q; int /*<<< orphan*/  p; int /*<<< orphan*/  d; int /*<<< orphan*/  e; int /*<<< orphan*/  n; } ;

/* Variables and functions */
 int /*<<< orphan*/  bignum_deinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (struct crypto_rsa_key*) ; 

void crypto_rsa_free(struct crypto_rsa_key *key)
{
	if (key) {
		bignum_deinit(key->n);
		bignum_deinit(key->e);
		bignum_deinit(key->d);
		bignum_deinit(key->p);
		bignum_deinit(key->q);
		bignum_deinit(key->dmp1);
		bignum_deinit(key->dmq1);
		bignum_deinit(key->iqmp);
		os_free(key);
	}
}