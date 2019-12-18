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
typedef  int u64 ;
typedef  scalar_t__ state ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int KHAZAD_ROUNDS ; 
 int const* T0 ; 
 int const* T1 ; 
 int const* T2 ; 
 int const* T3 ; 
 int const* T4 ; 
 int const* T5 ; 
 int const* T6 ; 
 int const* T7 ; 
 int const be64_to_cpu (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  cpu_to_be64 (int) ; 

__attribute__((used)) static void khazad_crypt(const u64 roundKey[KHAZAD_ROUNDS + 1],
		u8 *ciphertext, const u8 *plaintext)
{
	const __be64 *src = (const __be64 *)plaintext;
	__be64 *dst = (__be64 *)ciphertext;
	int r;
	u64 state;

	state = be64_to_cpu(*src) ^ roundKey[0];

	for (r = 1; r < KHAZAD_ROUNDS; r++) {
		state = T0[(int)(state >> 56)       ] ^
			T1[(int)(state >> 48) & 0xff] ^
			T2[(int)(state >> 40) & 0xff] ^
			T3[(int)(state >> 32) & 0xff] ^
			T4[(int)(state >> 24) & 0xff] ^
			T5[(int)(state >> 16) & 0xff] ^
			T6[(int)(state >>  8) & 0xff] ^
			T7[(int)(state      ) & 0xff] ^
			roundKey[r];
    	}

	state = (T0[(int)(state >> 56)       ] & 0xff00000000000000ULL) ^
		(T1[(int)(state >> 48) & 0xff] & 0x00ff000000000000ULL) ^
		(T2[(int)(state >> 40) & 0xff] & 0x0000ff0000000000ULL) ^
		(T3[(int)(state >> 32) & 0xff] & 0x000000ff00000000ULL) ^
		(T4[(int)(state >> 24) & 0xff] & 0x00000000ff000000ULL) ^
		(T5[(int)(state >> 16) & 0xff] & 0x0000000000ff0000ULL) ^
		(T6[(int)(state >>  8) & 0xff] & 0x000000000000ff00ULL) ^
		(T7[(int)(state      ) & 0xff] & 0x00000000000000ffULL) ^
		roundKey[KHAZAD_ROUNDS];

	*dst = cpu_to_be64(state);
}