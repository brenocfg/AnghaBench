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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  FLS (int) ; 
 int /*<<< orphan*/  ROUNDS (int) ; 
 int /*<<< orphan*/  SUBKEY_L (unsigned int) ; 
 int /*<<< orphan*/  SUBKEY_R (unsigned int) ; 

__attribute__((used)) static void camellia_do_encrypt(const u32 *subkey, u32 *io, unsigned max)
{
	u32 il,ir,t0,t1;               /* temporary variables */

	/* pre whitening but absorb kw2 */
	io[0] ^= SUBKEY_L(0);
	io[1] ^= SUBKEY_R(0);

	/* main iteration */
#define ROUNDS(i) do { \
	CAMELLIA_ROUNDSM(io[0],io[1], \
			 SUBKEY_L(i + 2),SUBKEY_R(i + 2), \
			 io[2],io[3],il,ir); \
	CAMELLIA_ROUNDSM(io[2],io[3], \
			 SUBKEY_L(i + 3),SUBKEY_R(i + 3), \
			 io[0],io[1],il,ir); \
	CAMELLIA_ROUNDSM(io[0],io[1], \
			 SUBKEY_L(i + 4),SUBKEY_R(i + 4), \
			 io[2],io[3],il,ir); \
	CAMELLIA_ROUNDSM(io[2],io[3], \
			 SUBKEY_L(i + 5),SUBKEY_R(i + 5), \
			 io[0],io[1],il,ir); \
	CAMELLIA_ROUNDSM(io[0],io[1], \
			 SUBKEY_L(i + 6),SUBKEY_R(i + 6), \
			 io[2],io[3],il,ir); \
	CAMELLIA_ROUNDSM(io[2],io[3], \
			 SUBKEY_L(i + 7),SUBKEY_R(i + 7), \
			 io[0],io[1],il,ir); \
} while (0)
#define FLS(i) do { \
	CAMELLIA_FLS(io[0],io[1],io[2],io[3], \
		     SUBKEY_L(i + 0),SUBKEY_R(i + 0), \
		     SUBKEY_L(i + 1),SUBKEY_R(i + 1), \
		     t0,t1,il,ir); \
} while (0)

	ROUNDS(0);
	FLS(8);
	ROUNDS(8);
	FLS(16);
	ROUNDS(16);
	if (max == 32) {
		FLS(24);
		ROUNDS(24);
	}

#undef ROUNDS
#undef FLS

	/* post whitening but kw4 */
	io[2] ^= SUBKEY_L(max);
	io[3] ^= SUBKEY_R(max);
	/* NB: io[0],[1] should be swapped with [2],[3] by caller! */
}