#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_5__ {scalar_t__* n; unsigned int nlen; scalar_t__* e; int elen; } ;
typedef  TYPE_1__ br_rsa_public_key ;
struct TYPE_6__ {unsigned int n_bitlen; int* p; int plen; int* q; int qlen; int* dp; size_t dplen; int* dq; size_t dqlen; int* iq; size_t iqlen; } ;
typedef  TYPE_2__ br_rsa_private_key ;
typedef  int /*<<< orphan*/  br_prng_class ;

/* Variables and functions */
 unsigned int BR_MAX_RSA_SIZE ; 
 unsigned int BR_MIN_RSA_SIZE ; 
 int MUL15 (int,int) ; 
 int TEMPS ; 
 int /*<<< orphan*/  br_enc32be (scalar_t__*,int) ; 
 int /*<<< orphan*/  br_i15_add (int*,int*,int) ; 
 int /*<<< orphan*/  br_i15_encode (int*,size_t,int*) ; 
 int br_i15_moddiv (int*,int*,int*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  br_i15_mulacc (int*,int*,int*) ; 
 int /*<<< orphan*/  br_i15_ninv15 (int) ; 
 int /*<<< orphan*/  br_i15_rshift (int*,int) ; 
 int br_i15_sub (int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_i15_zero (int*,int) ; 
 int /*<<< orphan*/  bufswap (int*,int*,int) ; 
 scalar_t__ invert_pubexp (int*,int*,int,int*) ; 
 int /*<<< orphan*/  mkprime (int /*<<< orphan*/  const**,int*,int,int,int*,size_t) ; 

uint32_t
br_rsa_i15_keygen(const br_prng_class **rng,
	br_rsa_private_key *sk, void *kbuf_priv,
	br_rsa_public_key *pk, void *kbuf_pub,
	unsigned size, uint32_t pubexp)
{
	uint32_t esize_p, esize_q;
	size_t plen, qlen, tlen;
	uint16_t *p, *q, *t;
	uint16_t tmp[TEMPS];
	uint32_t r;

	if (size < BR_MIN_RSA_SIZE || size > BR_MAX_RSA_SIZE) {
		return 0;
	}
	if (pubexp == 0) {
		pubexp = 3;
	} else if (pubexp == 1 || (pubexp & 1) == 0) {
		return 0;
	}

	esize_p = (size + 1) >> 1;
	esize_q = size - esize_p;
	sk->n_bitlen = size;
	sk->p = kbuf_priv;
	sk->plen = (esize_p + 7) >> 3;
	sk->q = sk->p + sk->plen;
	sk->qlen = (esize_q + 7) >> 3;
	sk->dp = sk->q + sk->qlen;
	sk->dplen = sk->plen;
	sk->dq = sk->dp + sk->dplen;
	sk->dqlen = sk->qlen;
	sk->iq = sk->dq + sk->dqlen;
	sk->iqlen = sk->plen;

	if (pk != NULL) {
		pk->n = kbuf_pub;
		pk->nlen = (size + 7) >> 3;
		pk->e = pk->n + pk->nlen;
		pk->elen = 4;
		br_enc32be(pk->e, pubexp);
		while (*pk->e == 0) {
			pk->e ++;
			pk->elen --;
		}
	}

	/*
	 * We now switch to encoded sizes.
	 *
	 * floor((x * 17477) / (2^18)) is equal to floor(x/15) for all
	 * integers x from 0 to 23833.
	 */
	esize_p += MUL15(esize_p, 17477) >> 18;
	esize_q += MUL15(esize_q, 17477) >> 18;
	plen = (esize_p + 15) >> 4;
	qlen = (esize_q + 15) >> 4;
	p = tmp;
	q = p + 1 + plen;
	t = q + 1 + qlen;
	tlen = ((sizeof tmp) / sizeof(uint16_t)) - (2 + plen + qlen);

	/*
	 * When looking for primes p and q, we temporarily divide
	 * candidates by 2, in order to compute the inverse of the
	 * public exponent.
	 */

	for (;;) {
		mkprime(rng, p, esize_p, pubexp, t, tlen);
		br_i15_rshift(p, 1);
		if (invert_pubexp(t, p, pubexp, t + 1 + plen)) {
			br_i15_add(p, p, 1);
			p[1] |= 1;
			br_i15_encode(sk->p, sk->plen, p);
			br_i15_encode(sk->dp, sk->dplen, t);
			break;
		}
	}

	for (;;) {
		mkprime(rng, q, esize_q, pubexp, t, tlen);
		br_i15_rshift(q, 1);
		if (invert_pubexp(t, q, pubexp, t + 1 + qlen)) {
			br_i15_add(q, q, 1);
			q[1] |= 1;
			br_i15_encode(sk->q, sk->qlen, q);
			br_i15_encode(sk->dq, sk->dqlen, t);
			break;
		}
	}

	/*
	 * If p and q have the same size, then it is possible that q > p
	 * (when the target modulus size is odd, we generate p with a
	 * greater bit length than q). If q > p, we want to swap p and q
	 * (and also dp and dq) for two reasons:
	 *  - The final step below (inversion of q modulo p) is easier if
	 *    p > q.
	 *  - While BearSSL's RSA code is perfectly happy with RSA keys such
	 *    that p < q, some other implementations have restrictions and
	 *    require p > q.
	 *
	 * Note that we can do a simple non-constant-time swap here,
	 * because the only information we leak here is that we insist on
	 * returning p and q such that p > q, which is not a secret.
	 */
	if (esize_p == esize_q && br_i15_sub(p, q, 0) == 1) {
		bufswap(p, q, (1 + plen) * sizeof *p);
		bufswap(sk->p, sk->q, sk->plen);
		bufswap(sk->dp, sk->dq, sk->dplen);
	}

	/*
	 * We have produced p, q, dp and dq. We can now compute iq = 1/d mod p.
	 *
	 * We ensured that p >= q, so this is just a matter of updating the
	 * header word for q (and possibly adding an extra word).
	 *
	 * Theoretically, the call below may fail, in case we were
	 * extraordinarily unlucky, and p = q. Another failure case is if
	 * Miller-Rabin failed us _twice_, and p and q are non-prime and
	 * have a factor is common. We report the error mostly because it
	 * is cheap and we can, but in practice this never happens (or, at
	 * least, it happens way less often than hardware glitches).
	 */
	q[0] = p[0];
	if (plen > qlen) {
		q[plen] = 0;
		t ++;
		tlen --;
	}
	br_i15_zero(t, p[0]);
	t[1] = 1;
	r = br_i15_moddiv(t, q, p, br_i15_ninv15(p[1]), t + 1 + plen);
	br_i15_encode(sk->iq, sk->iqlen, t);

	/*
	 * Compute the public modulus too, if required.
	 */
	if (pk != NULL) {
		br_i15_zero(t, p[0]);
		br_i15_mulacc(t, p, q);
		br_i15_encode(pk->n, pk->nlen, t);
	}

	return r;
}