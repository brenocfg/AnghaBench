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
struct crypto_rsa_key {int /*<<< orphan*/  n; int /*<<< orphan*/  e; int /*<<< orphan*/  q; int /*<<< orphan*/  p; int /*<<< orphan*/  iqmp; int /*<<< orphan*/  dmq1; int /*<<< orphan*/  dmp1; int /*<<< orphan*/  private_key; } ;
struct bignum {int dummy; } ;

/* Variables and functions */
 scalar_t__ bignum_add (struct bignum*,struct bignum*,struct bignum*) ; 
 scalar_t__ bignum_cmp (int /*<<< orphan*/ ,struct bignum*) ; 
 int /*<<< orphan*/  bignum_deinit (struct bignum*) ; 
 scalar_t__ bignum_exptmod (struct bignum*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bignum*) ; 
 scalar_t__ bignum_get_unsigned_bin (struct bignum*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t bignum_get_unsigned_bin_len (struct bignum*) ; 
 struct bignum* bignum_init () ; 
 scalar_t__ bignum_mul (struct bignum*,int /*<<< orphan*/ ,struct bignum*) ; 
 scalar_t__ bignum_mulmod (struct bignum*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bignum*) ; 
 scalar_t__ bignum_set_unsigned_bin (struct bignum*,int /*<<< orphan*/  const*,size_t) ; 
 scalar_t__ bignum_sub (struct bignum*,struct bignum*,struct bignum*) ; 
 size_t crypto_rsa_get_modulus_len (struct crypto_rsa_key*) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

int crypto_rsa_exptmod(const u8 *in, size_t inlen, u8 *out, size_t *outlen,
		       struct crypto_rsa_key *key, int use_private)
{
	struct bignum *tmp, *a = NULL, *b = NULL;
	int ret = -1;
	size_t modlen;

	if (use_private && !key->private_key)
		return -1;

	tmp = bignum_init();
	if (tmp == NULL)
		return -1;

	if (bignum_set_unsigned_bin(tmp, in, inlen) < 0)
		goto error;
	if (bignum_cmp(key->n, tmp) < 0) {
		/* Too large input value for the RSA key modulus */
		goto error;
	}

	if (use_private) {
		/*
		 * Decrypt (or sign) using Chinese remainer theorem to speed
		 * up calculation. This is equivalent to tmp = tmp^d mod n
		 * (which would require more CPU to calculate directly).
		 *
		 * dmp1 = (1/e) mod (p-1)
		 * dmq1 = (1/e) mod (q-1)
		 * iqmp = (1/q) mod p, where p > q
		 * m1 = c^dmp1 mod p
		 * m2 = c^dmq1 mod q
		 * h = q^-1 (m1 - m2) mod p
		 * m = m2 + hq
		 */
		a = bignum_init();
		b = bignum_init();
		if (a == NULL || b == NULL)
			goto error;

		/* a = tmp^dmp1 mod p */
		if (bignum_exptmod(tmp, key->dmp1, key->p, a) < 0)
			goto error;

		/* b = tmp^dmq1 mod q */
		if (bignum_exptmod(tmp, key->dmq1, key->q, b) < 0)
			goto error;

		/* tmp = (a - b) * (1/q mod p) (mod p) */
		if (bignum_sub(a, b, tmp) < 0 ||
		    bignum_mulmod(tmp, key->iqmp, key->p, tmp) < 0)
			goto error;

		/* tmp = b + q * tmp */
		if (bignum_mul(tmp, key->q, tmp) < 0 ||
		    bignum_add(tmp, b, tmp) < 0)
			goto error;
	} else {
		/* Encrypt (or verify signature) */
		/* tmp = tmp^e mod N */
		if (bignum_exptmod(tmp, key->e, key->n, tmp) < 0)
			goto error;
	}

	modlen = crypto_rsa_get_modulus_len(key);
	if (modlen > *outlen) {
		*outlen = modlen;
		goto error;
	}

	if (bignum_get_unsigned_bin_len(tmp) > modlen)
		goto error; /* should never happen */

	*outlen = modlen;
	os_memset(out, 0, modlen);
	if (bignum_get_unsigned_bin(
		    tmp, out +
		    (modlen - bignum_get_unsigned_bin_len(tmp)), NULL) < 0)
		goto error;

	ret = 0;

error:

	bignum_deinit(tmp);
	bignum_deinit(a);
	bignum_deinit(b);
	return ret;
}