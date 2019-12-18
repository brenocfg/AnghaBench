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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  br_prng_class ;

/* Variables and functions */
 int GT (int,int) ; 
 scalar_t__ miller_rabin (int /*<<< orphan*/  const**,int*,int,int*,size_t) ; 
 int /*<<< orphan*/  mkrand (int /*<<< orphan*/  const**,int*,int) ; 
 int /*<<< orphan*/  trial_divisions (int*,int*) ; 

__attribute__((used)) static void
mkprime(const br_prng_class **rng, uint16_t *x, uint32_t esize,
	uint32_t pubexp, uint16_t *t, size_t tlen)
{
	size_t len;

	x[0] = esize;
	len = (esize + 15) >> 4;
	for (;;) {
		size_t u;
		uint32_t m3, m5, m7, m11;
		int rounds;

		/*
		 * Generate random bits. We force the two top bits and the
		 * two bottom bits to 1.
		 */
		mkrand(rng, x, esize);
		if ((esize & 15) == 0) {
			x[len] |= 0x6000;
		} else if ((esize & 15) == 1) {
			x[len] |= 0x0001;
			x[len - 1] |= 0x4000;
		} else {
			x[len] |= 0x0003 << ((esize & 15) - 2);
		}
		x[1] |= 0x0003;

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
		for (u = 0; u < len; u ++) {
			uint32_t w;

			w = x[1 + u];
			m3 += w << (u & 1);
			m3 = (m3 & 0xFF) + (m3 >> 8);
			m5 += w << ((4 - u) & 3);
			m5 = (m5 & 0xFF) + (m5 >> 8);
			m7 += w;
			m7 = (m7 & 0x1FF) + (m7 >> 9);
			m11 += w << (5 & -(u & 1));
			m11 = (m11 & 0x3FF) + (m11 >> 10);
		}

		/*
		 * Maximum values of m* at this point:
		 *  m3:   511
		 *  m5:   2310
		 *  m7:   510
		 *  m11:  2047
		 * We use the same properties to make further reductions.
		 */

		m3 = (m3 & 0x0F) + (m3 >> 4);      /* max: 46 */
		m3 = (m3 & 0x0F) + (m3 >> 4);      /* max: 16 */
		m3 = ((m3 * 43) >> 5) & 3;

		m5 = (m5 & 0xFF) + (m5 >> 8);      /* max: 263 */
		m5 = (m5 & 0x0F) + (m5 >> 4);      /* max: 30 */
		m5 = (m5 & 0x0F) + (m5 >> 4);      /* max: 15 */
		m5 -= 10 & -GT(m5, 9);
		m5 -= 5 & -GT(m5, 4);

		m7 = (m7 & 0x3F) + (m7 >> 6);      /* max: 69 */
		m7 = (m7 & 7) + (m7 >> 3);         /* max: 14 */
		m7 = ((m7 * 147) >> 7) & 7;

		/*
		 * 2^5 = 32 = -1 mod 11.
		 */
		m11 = (m11 & 0x1F) + 66 - (m11 >> 5);   /* max: 97 */
		m11 -= 88 & -GT(m11, 87);
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
		if (esize < 320) {
			rounds = 12;
		} else if (esize < 480) {
			rounds = 9;
		} else if (esize < 693) {
			rounds = 6;
		} else if (esize < 906) {
			rounds = 4;
		} else if (esize < 1386) {
			rounds = 3;
		} else {
			rounds = 2;
		}

		if (miller_rabin(rng, x, rounds, t, tlen)) {
			return;
		}
	}
}