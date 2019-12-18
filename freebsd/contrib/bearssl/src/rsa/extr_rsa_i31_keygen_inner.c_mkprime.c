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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  br_prng_class ;
typedef  int /*<<< orphan*/  br_i31_modpow_opt_type ;

/* Variables and functions */
 int GT (int,int) ; 
 scalar_t__ miller_rabin (int /*<<< orphan*/  const**,int*,int,int*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mkrand (int /*<<< orphan*/  const**,int*,int) ; 
 int /*<<< orphan*/  trial_divisions (int*,int*) ; 

__attribute__((used)) static void
mkprime(const br_prng_class **rng, uint32_t *x, uint32_t esize,
	uint32_t pubexp, uint32_t *t, size_t tlen, br_i31_modpow_opt_type mp31)
{
	size_t len;

	x[0] = esize;
	len = (esize + 31) >> 5;
	for (;;) {
		size_t u;
		uint32_t m3, m5, m7, m11;
		int rounds, s7, s11;

		/*
		 * Generate random bits. We force the two top bits and the
		 * two bottom bits to 1.
		 */
		mkrand(rng, x, esize);
		if ((esize & 31) == 0) {
			x[len] |= 0x60000000;
		} else if ((esize & 31) == 1) {
			x[len] |= 0x00000001;
			x[len - 1] |= 0x40000000;
		} else {
			x[len] |= 0x00000003 << ((esize & 31) - 2);
		}
		x[1] |= 0x00000003;

		/*
		 * Trial division with low primes (3, 5, 7 and 11). We
		 * use the following properties:
		 *
		 *   2^2 = 1 mod 3
		 *   2^4 = 1 mod 5
		 *   2^3 = 1 mod 7
		 *   2^10 = 1 mod 11
		 */
		m3 = 0;
		m5 = 0;
		m7 = 0;
		m11 = 0;
		s7 = 0;
		s11 = 0;
		for (u = 0; u < len; u ++) {
			uint32_t w, w3, w5, w7, w11;

			w = x[1 + u];
			w3 = (w & 0xFFFF) + (w >> 16);     /* max: 98302 */
			w5 = (w & 0xFFFF) + (w >> 16);     /* max: 98302 */
			w7 = (w & 0x7FFF) + (w >> 15);     /* max: 98302 */
			w11 = (w & 0xFFFFF) + (w >> 20);   /* max: 1050622 */

			m3 += w3 << (u & 1);
			m3 = (m3 & 0xFF) + (m3 >> 8);      /* max: 1025 */

			m5 += w5 << ((4 - u) & 3);
			m5 = (m5 & 0xFFF) + (m5 >> 12);    /* max: 4479 */

			m7 += w7 << s7;
			m7 = (m7 & 0x1FF) + (m7 >> 9);     /* max: 1280 */
			if (++ s7 == 3) {
				s7 = 0;
			}

			m11 += w11 << s11;
			if (++ s11 == 10) {
				s11 = 0;
			}
			m11 = (m11 & 0x3FF) + (m11 >> 10); /* max: 526847 */
		}

		m3 = (m3 & 0x3F) + (m3 >> 6);      /* max: 78 */
		m3 = (m3 & 0x0F) + (m3 >> 4);      /* max: 18 */
		m3 = ((m3 * 43) >> 5) & 3;

		m5 = (m5 & 0xFF) + (m5 >> 8);      /* max: 271 */
		m5 = (m5 & 0x0F) + (m5 >> 4);      /* max: 31 */
		m5 -= 20 & -GT(m5, 19);
		m5 -= 10 & -GT(m5, 9);
		m5 -= 5 & -GT(m5, 4);

		m7 = (m7 & 0x3F) + (m7 >> 6);      /* max: 82 */
		m7 = (m7 & 0x07) + (m7 >> 3);      /* max: 16 */
		m7 = ((m7 * 147) >> 7) & 7;

		/*
		 * 2^5 = 32 = -1 mod 11.
		 */
		m11 = (m11 & 0x3FF) + (m11 >> 10);      /* max: 1536 */
		m11 = (m11 & 0x3FF) + (m11 >> 10);      /* max: 1023 */
		m11 = (m11 & 0x1F) + 33 - (m11 >> 5);   /* max: 64 */
		m11 -= 44 & -GT(m11, 43);
		m11 -= 22 & -GT(m11, 21);
		m11 -= 11 & -GT(m11, 10);

		/*
		 * If any of these modulo is 0, then the candidate is
		 * not prime. Also, if pubexp is 3, 5, 7 or 11, and the
		 * corresponding modulus is 1, then the candidate must
		 * be rejected, because we need e to be invertible
		 * modulo p-1. We can use simple comparisons here
		 * because they won't leak information on a candidate
		 * that we keep, only on one that we reject (and is thus
		 * not secret).
		 */
		if (m3 == 0 || m5 == 0 || m7 == 0 || m11 == 0) {
			continue;
		}
		if ((pubexp == 3 && m3 == 1)
			|| (pubexp == 5 && m5 == 5)
			|| (pubexp == 7 && m5 == 7)
			|| (pubexp == 11 && m5 == 11))
		{
			continue;
		}

		/*
		 * More trial divisions.
		 */
		if (!trial_divisions(x, t)) {
			continue;
		}

		/*
		 * Miller-Rabin algorithm. Since we selected a random
		 * integer, not a maliciously crafted integer, we can use
		 * relatively few rounds to lower the risk of a false
		 * positive (i.e. declaring prime a non-prime) under
		 * 2^(-80). It is not useful to lower the probability much
		 * below that, since that would be substantially below
		 * the probability of the hardware misbehaving. Sufficient
		 * numbers of rounds are extracted from the Handbook of
		 * Applied Cryptography, note 4.49 (page 149).
		 *
		 * Since we work on the encoded size (esize), we need to
		 * compare with encoded thresholds.
		 */
		if (esize < 309) {
			rounds = 12;
		} else if (esize < 464) {
			rounds = 9;
		} else if (esize < 670) {
			rounds = 6;
		} else if (esize < 877) {
			rounds = 4;
		} else if (esize < 1341) {
			rounds = 3;
		} else {
			rounds = 2;
		}

		if (miller_rabin(rng, x, rounds, t, tlen, mp31)) {
			return;
		}
	}
}