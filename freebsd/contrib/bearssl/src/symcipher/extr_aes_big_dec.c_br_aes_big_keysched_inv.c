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

/* Variables and functions */
 unsigned int br_aes_keysched (int*,void const*,size_t) ; 
 int mul9 (unsigned int) ; 
 int mulb (unsigned int) ; 
 int muld (unsigned int) ; 
 int mule (unsigned int) ; 

unsigned
br_aes_big_keysched_inv(uint32_t *skey, const void *key, size_t key_len)
{
	unsigned num_rounds;
	int i, m;

	/*
	 * Sub-keys for decryption are distinct from encryption sub-keys
	 * in that InvMixColumns() is already applied for the inner
	 * rounds.
	 */
	num_rounds = br_aes_keysched(skey, key, key_len);
	m = (int)(num_rounds << 2);
	for (i = 4; i < m; i ++) {
		uint32_t p;
		unsigned p0, p1, p2, p3;
		uint32_t q0, q1, q2, q3;

		p = skey[i];
		p0 = p >> 24;
		p1 = (p >> 16) & 0xFF;
		p2 = (p >> 8) & 0xFF;
		p3 = p & 0xFF;
		q0 = mule(p0) ^ mulb(p1) ^ muld(p2) ^ mul9(p3);
		q1 = mul9(p0) ^ mule(p1) ^ mulb(p2) ^ muld(p3);
		q2 = muld(p0) ^ mul9(p1) ^ mule(p2) ^ mulb(p3);
		q3 = mulb(p0) ^ muld(p1) ^ mul9(p2) ^ mule(p3);
		skey[i] = (q0 << 24) | (q1 << 16) | (q2 << 8) | q3;
	}
	return num_rounds;
}