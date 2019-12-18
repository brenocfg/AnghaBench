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
typedef  int u_int8_t ;
typedef  int u_int32_t ;

/* Variables and functions */
 int MH3_X86_32_C1 ; 
 int MH3_X86_32_C2 ; 
 int ROTL32 (int,int) ; 
 int getblock32 (int const*,int) ; 
 int mh3_fmix32 (int) ; 

u_int32_t
net_flowhash_mh3_x86_32(const void *key, u_int32_t len, const u_int32_t seed)
{
	const u_int8_t *data = (const u_int8_t *)key;
	const u_int32_t nblocks = len / 4;
	const u_int32_t *blocks;
	const u_int8_t *tail;
	u_int32_t h1 = seed, k1;
	int i;

	/* body */
	blocks = (const u_int32_t *)(const void *)(data + nblocks * 4);

	for (i = -nblocks; i; i++) {
		k1 = getblock32(blocks, i);

		k1 *= MH3_X86_32_C1;
		k1 = ROTL32(k1, 15);
		k1 *= MH3_X86_32_C2;

		h1 ^= k1;
		h1 = ROTL32(h1, 13);
		h1 = h1 * 5 + 0xe6546b64;
	}

	/* tail */
	tail = (const u_int8_t *)(const void *)(data + nblocks * 4);
	k1 = 0;

	switch (len & 3) {
	case 3:
		k1 ^= tail[2] << 16;
		/* FALLTHRU */
	case 2:
		k1 ^= tail[1] << 8;
		/* FALLTHRU */
	case 1:
		k1 ^= tail[0];
		k1 *= MH3_X86_32_C1;
		k1 = ROTL32(k1, 15);
		k1 *= MH3_X86_32_C2;
		h1 ^= k1;
	};

	/* finalization */
	h1 ^= len;

	h1 = mh3_fmix32(h1);

	return (h1);
}