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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  br_hmac_drbg_context ;

/* Variables and functions */
 int /*<<< orphan*/  br_hmac_drbg_generate (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  br_hmac_drbg_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  br_i15_decode (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  br_i15_decode_mod (int /*<<< orphan*/ *,unsigned char*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_i15_encode (unsigned char*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_i15_modpow_opt (int /*<<< orphan*/ *,unsigned char*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  br_i15_ninv15 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_i31_decode (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  br_i31_decode_mod (int /*<<< orphan*/ *,unsigned char*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_i31_encode (unsigned char*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_i31_ninv31 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_i62_modpow_opt (int /*<<< orphan*/ *,unsigned char*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  br_sha256_vtable ; 
 int /*<<< orphan*/  check_equals (char*,unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
test_modpow_i62(void)
{
	br_hmac_drbg_context hc;
	int k;

	printf("Test ModPow/i62: ");

	br_hmac_drbg_init(&hc, &br_sha256_vtable, "seed modpow", 11);
	for (k = 10; k <= 500; k ++) {
		size_t blen;
		unsigned char bm[128], bx[128], bx1[128], bx2[128];
		unsigned char be[128];
		unsigned mask;
		uint32_t x1[35], m1[35];
		uint16_t x2[70], m2[70];
		uint64_t tmp1[500];
		uint16_t tmp2[2000];

		blen = (k + 7) >> 3;
		br_hmac_drbg_generate(&hc, bm, blen);
		br_hmac_drbg_generate(&hc, bx, blen);
		br_hmac_drbg_generate(&hc, be, blen);
		bm[blen - 1] |= 0x01;
		mask = 0xFF >> ((int)(blen << 3) - k);
		bm[0] &= mask;
		bm[0] |= (mask - (mask >> 1));
		bx[0] &= (mask >> 1);

		br_i31_decode(m1, bm, blen);
		br_i31_decode_mod(x1, bx, blen, m1);
		br_i62_modpow_opt(x1, be, blen, m1, br_i31_ninv31(m1[1]),
			tmp1, (sizeof tmp1) / (sizeof tmp1[0]));
		br_i31_encode(bx1, blen, x1);

		br_i15_decode(m2, bm, blen);
		br_i15_decode_mod(x2, bx, blen, m2);
		br_i15_modpow_opt(x2, be, blen, m2, br_i15_ninv15(m2[1]),
			tmp2, (sizeof tmp2) / (sizeof tmp2[0]));
		br_i15_encode(bx2, blen, x2);

		check_equals("ModPow i62/i15", bx1, bx2, blen);

		printf(".");
		fflush(stdout);
	}

	printf(" done.\n");
	fflush(stdout);
}