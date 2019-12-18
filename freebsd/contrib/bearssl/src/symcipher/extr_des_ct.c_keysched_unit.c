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
 int* QL0 ; 
 int* QL1 ; 
 int* QR0 ; 
 int* QR1 ; 
 int /*<<< orphan*/  br_des_keysched_unit (int*,void const*) ; 
 int kl ; 
 int kr ; 
 int rotl (int,int) ; 
 int sk0 ; 
 int sk1 ; 

__attribute__((used)) static void
keysched_unit(uint32_t *skey, const void *key)
{
	int i;

	br_des_keysched_unit(skey, key);

	/*
	 * Apply PC-2 + bitslicing.
	 */
	for (i = 0; i < 16; i ++) {
		uint32_t kl, kr, sk0, sk1;
		int j;

		kl = skey[(i << 1) + 0];
		kr = skey[(i << 1) + 1];
		sk0 = 0;
		sk1 = 0;
		for (j = 0; j < 16; j ++) {
			sk0 <<= 1;
			sk1 <<= 1;
			sk0 |= ((kl >> QL0[j]) & (uint32_t)1) << 16;
			sk0 |= (kr >> QR0[j]) & (uint32_t)1;
			sk1 |= ((kl >> QL1[j]) & (uint32_t)1) << 16;
			sk1 |= (kr >> QR1[j]) & (uint32_t)1;
		}

		skey[(i << 1) + 0] = sk0;
		skey[(i << 1) + 1] = sk1;
	}

#if 0
		/*
		 * Speed-optimized version for PC-2 + bitslicing.
		 * (Unused. Kept for reference only.)
		 */
		sk0 = kl & (uint32_t)0x00100000;
		sk0 |= (kl & (uint32_t)0x08008000) << 2;
		sk0 |= (kl & (uint32_t)0x00400000) << 4;
		sk0 |= (kl & (uint32_t)0x00800000) << 5;
		sk0 |= (kl & (uint32_t)0x00040000) << 6;
		sk0 |= (kl & (uint32_t)0x00010000) << 7;
		sk0 |= (kl & (uint32_t)0x00000100) << 10;
		sk0 |= (kl & (uint32_t)0x00022000) << 14;
		sk0 |= (kl & (uint32_t)0x00000082) << 18;
		sk0 |= (kl & (uint32_t)0x00000004) << 19;
		sk0 |= (kl & (uint32_t)0x04000000) >> 10;
		sk0 |= (kl & (uint32_t)0x00000010) << 26;
		sk0 |= (kl & (uint32_t)0x01000000) >> 2;

		sk0 |= kr & (uint32_t)0x00000100;
		sk0 |= (kr & (uint32_t)0x00000008) << 1;
		sk0 |= (kr & (uint32_t)0x00000200) << 4;
		sk0 |= rotl(kr & (uint32_t)0x08000021, 6);
		sk0 |= (kr & (uint32_t)0x01000000) >> 24;
		sk0 |= (kr & (uint32_t)0x00000002) << 11;
		sk0 |= (kr & (uint32_t)0x00100000) >> 18;
		sk0 |= (kr & (uint32_t)0x00400000) >> 17;
		sk0 |= (kr & (uint32_t)0x00800000) >> 14;
		sk0 |= (kr & (uint32_t)0x02020000) >> 10;
		sk0 |= (kr & (uint32_t)0x00080000) >> 5;
		sk0 |= (kr & (uint32_t)0x00000040) >> 3;
		sk0 |= (kr & (uint32_t)0x00000800) >> 1;

		sk1 = kl & (uint32_t)0x02000000;
		sk1 |= (kl & (uint32_t)0x00001000) << 5;
		sk1 |= (kl & (uint32_t)0x00000200) << 11;
		sk1 |= (kl & (uint32_t)0x00004000) << 15;
		sk1 |= (kl & (uint32_t)0x00000020) << 16;
		sk1 |= (kl & (uint32_t)0x00000800) << 17;
		sk1 |= (kl & (uint32_t)0x00000001) << 24;
		sk1 |= (kl & (uint32_t)0x00200000) >> 5;

		sk1 |= (kr & (uint32_t)0x00000010) << 8;
		sk1 |= (kr & (uint32_t)0x04000000) >> 17;
		sk1 |= (kr & (uint32_t)0x00004000) >> 14;
		sk1 |= (kr & (uint32_t)0x00000400) >> 9;
		sk1 |= (kr & (uint32_t)0x00010000) >> 8;
		sk1 |= (kr & (uint32_t)0x00001000) >> 7;
		sk1 |= (kr & (uint32_t)0x00000080) >> 3;
		sk1 |= (kr & (uint32_t)0x00008000) >> 2;
#endif
}