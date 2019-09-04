#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* P; } ;
struct TYPE_4__ {TYPE_1__ s; } ;
typedef  int BF_word ;
typedef  int* BF_key ;

/* Variables and functions */
 int BF_N ; 
 TYPE_2__ BF_init_state ; 

__attribute__((used)) static void BF_set_key(const char *key, BF_key expanded, BF_key initial,
    unsigned char flags)
{
	const char *ptr = key;
	unsigned int bug, i, j;
	BF_word safety, sign, diff, tmp[2];

/*
 * There was a sign extension bug in older revisions of this function.  While
 * we would have liked to simply fix the bug and move on, we have to provide
 * a backwards compatibility feature (essentially the bug) for some systems and
 * a safety measure for some others.  The latter is needed because for certain
 * multiple inputs to the buggy algorithm there exist easily found inputs to
 * the correct algorithm that produce the same hash.  Thus, we optionally
 * deviate from the correct algorithm just enough to avoid such collisions.
 * While the bug itself affected the majority of passwords containing
 * characters with the 8th bit set (although only a percentage of those in a
 * collision-producing way), the anti-collision safety measure affects
 * only a subset of passwords containing the '\xff' character (not even all of
 * those passwords, just some of them).  This character is not found in valid
 * UTF-8 sequences and is rarely used in popular 8-bit character encodings.
 * Thus, the safety measure is unlikely to cause much annoyance, and is a
 * reasonable tradeoff to use when authenticating against existing hashes that
 * are not reliably known to have been computed with the correct algorithm.
 *
 * We use an approach that tries to minimize side-channel leaks of password
 * information - that is, we mostly use fixed-cost bitwise operations instead
 * of branches or table lookups.  (One conditional branch based on password
 * length remains.  It is not part of the bug aftermath, though, and is
 * difficult and possibly unreasonable to avoid given the use of C strings by
 * the caller, which results in similar timing leaks anyway.)
 *
 * For actual implementation, we set an array index in the variable "bug"
 * (0 means no bug, 1 means sign extension bug emulation) and a flag in the
 * variable "safety" (bit 16 is set when the safety measure is requested).
 * Valid combinations of settings are:
 *
 * Prefix "$2a$": bug = 0, safety = 0x10000
 * Prefix "$2x$": bug = 1, safety = 0
 * Prefix "$2y$": bug = 0, safety = 0
 */
	bug = flags & 1;
	safety = ((BF_word)flags & 2) << 15;

	sign = diff = 0;

	for (i = 0; i < BF_N + 2; i++) {
		tmp[0] = tmp[1] = 0;
		for (j = 0; j < 4; j++) {
			tmp[0] <<= 8;
			tmp[0] |= (unsigned char)*ptr; /* correct */
			tmp[1] <<= 8;
			tmp[1] |= (signed char)*ptr; /* bug */
/*
 * Sign extension in the first char has no effect - nothing to overwrite yet,
 * and those extra 24 bits will be fully shifted out of the 32-bit word.  For
 * chars 2, 3, 4 in each four-char block, we set bit 7 of "sign" if sign
 * extension in tmp[1] occurs.  Once this flag is set, it remains set.
 */
			if (j)
				sign |= tmp[1] & 0x80;
			if (!*ptr)
				ptr = key;
			else
				ptr++;
		}
		diff |= tmp[0] ^ tmp[1]; /* Non-zero on any differences */

		expanded[i] = tmp[bug];
		initial[i] = BF_init_state.s.P[i] ^ tmp[bug];
	}

/*
 * At this point, "diff" is zero iff the correct and buggy algorithms produced
 * exactly the same result.  If so and if "sign" is non-zero, which indicates
 * that there was a non-benign sign extension, this means that we have a
 * collision between the correctly computed hash for this password and a set of
 * passwords that could be supplied to the buggy algorithm.  Our safety measure
 * is meant to protect from such many-buggy to one-correct collisions, by
 * deviating from the correct algorithm in such cases.  Let's check for this.
 */
	diff |= diff >> 16; /* still zero iff exact match */
	diff &= 0xffff; /* ditto */
	diff += 0xffff; /* bit 16 set iff "diff" was non-zero (on non-match) */
	sign <<= 9; /* move the non-benign sign extension flag to bit 16 */
	sign &= ~diff & safety; /* action needed? */

/*
 * If we have determined that we need to deviate from the correct algorithm,
 * flip bit 16 in initial expanded key.  (The choice of 16 is arbitrary, but
 * let's stick to it now.  It came out of the approach we used above, and it's
 * not any worse than any other choice we could make.)
 *
 * It is crucial that we don't do the same to the expanded key used in the main
 * Eksblowfish loop.  By doing it to only one of these two, we deviate from a
 * state that could be directly specified by a password to the buggy algorithm
 * (and to the fully correct one as well, but that's a side-effect).
 */
	initial[0] ^= sign;
}