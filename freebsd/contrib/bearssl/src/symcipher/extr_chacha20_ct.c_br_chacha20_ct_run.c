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
 int /*<<< orphan*/  QROUND (int,int,int,int) ; 
 int br_dec32le (unsigned char const*) ; 
 int /*<<< orphan*/  br_enc32le (unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 

uint32_t
br_chacha20_ct_run(const void *key,
	const void *iv, uint32_t cc, void *data, size_t len)
{
	unsigned char *buf;
	uint32_t kw[8], ivw[3];
	size_t u;

	static const uint32_t CW[] = {
		0x61707865, 0x3320646e, 0x79622d32, 0x6b206574
	};

	buf = data;
	for (u = 0; u < 8; u ++) {
		kw[u] = br_dec32le((const unsigned char *)key + (u << 2));
	}
	for (u = 0; u < 3; u ++) {
		ivw[u] = br_dec32le((const unsigned char *)iv + (u << 2));
	}
	while (len > 0) {
		uint32_t state[16];
		int i;
		size_t clen;
		unsigned char tmp[64];

		memcpy(&state[0], CW, sizeof CW);
		memcpy(&state[4], kw, sizeof kw);
		state[12] = cc;
		memcpy(&state[13], ivw, sizeof ivw);
		for (i = 0; i < 10; i ++) {

#define QROUND(a, b, c, d)   do { \
		state[a] += state[b]; \
		state[d] ^= state[a]; \
		state[d] = (state[d] << 16) | (state[d] >> 16); \
		state[c] += state[d]; \
		state[b] ^= state[c]; \
		state[b] = (state[b] << 12) | (state[b] >> 20); \
		state[a] += state[b]; \
		state[d] ^= state[a]; \
		state[d] = (state[d] <<  8) | (state[d] >> 24); \
		state[c] += state[d]; \
		state[b] ^= state[c]; \
		state[b] = (state[b] <<  7) | (state[b] >> 25); \
	} while (0)

			QROUND( 0,  4,  8, 12);
			QROUND( 1,  5,  9, 13);
			QROUND( 2,  6, 10, 14);
			QROUND( 3,  7, 11, 15);
			QROUND( 0,  5, 10, 15);
			QROUND( 1,  6, 11, 12);
			QROUND( 2,  7,  8, 13);
			QROUND( 3,  4,  9, 14);

#undef QROUND

		}
		for (u = 0; u < 4; u ++) {
			br_enc32le(&tmp[u << 2], state[u] + CW[u]);
		}
		for (u = 4; u < 12; u ++) {
			br_enc32le(&tmp[u << 2], state[u] + kw[u - 4]);
		}
		br_enc32le(&tmp[48], state[12] + cc);
		for (u = 13; u < 16; u ++) {
			br_enc32le(&tmp[u << 2], state[u] + ivw[u - 13]);
		}

		clen = len < 64 ? len : 64;
		for (u = 0; u < clen; u ++) {
			buf[u] ^= tmp[u];
		}
		buf += clen;
		len -= clen;
		cc ++;
	}
	return cc;
}