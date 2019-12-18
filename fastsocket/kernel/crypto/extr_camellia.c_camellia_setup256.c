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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CAMELLIA_F (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA1L ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA1R ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA2L ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA2R ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA3L ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA3R ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA4L ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA4R ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA5L ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA5R ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA6L ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA6R ; 
 int /*<<< orphan*/  ROLDQ (int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  ROLDQo32 (int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  camellia_setup_tail (int*,int*,int*,int) ; 
 int get_unaligned_be32 (unsigned char const*) ; 

__attribute__((used)) static void camellia_setup256(const unsigned char *key, u32 *subkey)
{
	u32 kll, klr, krl, krr;        /* left half of key */
	u32 krll, krlr, krrl, krrr;    /* right half of key */
	u32 il, ir, t0, t1, w0, w1;    /* temporary variables */
	u32 subL[34];
	u32 subR[34];

	/**
	 *  key = (kll || klr || krl || krr || krll || krlr || krrl || krrr)
	 *  (|| is concatenation)
	 */
	kll = get_unaligned_be32(key);
	klr = get_unaligned_be32(key + 4);
	krl = get_unaligned_be32(key + 8);
	krr = get_unaligned_be32(key + 12);
	krll = get_unaligned_be32(key + 16);
	krlr = get_unaligned_be32(key + 20);
	krrl = get_unaligned_be32(key + 24);
	krrr = get_unaligned_be32(key + 28);

	/* generate KL dependent subkeys */
	/* kw1 */
	subL[0] = kll; subR[0] = klr;
	/* kw2 */
	subL[1] = krl; subR[1] = krr;
	ROLDQo32(kll, klr, krl, krr, w0, w1, 45);
	/* k9 */
	subL[12] = kll; subR[12] = klr;
	/* k10 */
	subL[13] = krl; subR[13] = krr;
	ROLDQ(kll, klr, krl, krr, w0, w1, 15);
	/* kl3 */
	subL[16] = kll; subR[16] = klr;
	/* kl4 */
	subL[17] = krl; subR[17] = krr;
	ROLDQ(kll, klr, krl, krr, w0, w1, 17);
	/* k17 */
	subL[22] = kll; subR[22] = klr;
	/* k18 */
	subL[23] = krl; subR[23] = krr;
	ROLDQo32(kll, klr, krl, krr, w0, w1, 34);
	/* k23 */
	subL[30] = kll; subR[30] = klr;
	/* k24 */
	subL[31] = krl; subR[31] = krr;

	/* generate KR dependent subkeys */
	ROLDQ(krll, krlr, krrl, krrr, w0, w1, 15);
	/* k3 */
	subL[4] = krll; subR[4] = krlr;
	/* k4 */
	subL[5] = krrl; subR[5] = krrr;
	ROLDQ(krll, krlr, krrl, krrr, w0, w1, 15);
	/* kl1 */
	subL[8] = krll; subR[8] = krlr;
	/* kl2 */
	subL[9] = krrl; subR[9] = krrr;
	ROLDQ(krll, krlr, krrl, krrr, w0, w1, 30);
	/* k13 */
	subL[18] = krll; subR[18] = krlr;
	/* k14 */
	subL[19] = krrl; subR[19] = krrr;
	ROLDQo32(krll, krlr, krrl, krrr, w0, w1, 34);
	/* k19 */
	subL[26] = krll; subR[26] = krlr;
	/* k20 */
	subL[27] = krrl; subR[27] = krrr;
	ROLDQo32(krll, krlr, krrl, krrr, w0, w1, 34);

	/* generate KA */
	kll = subL[0] ^ krll; klr = subR[0] ^ krlr;
	krl = subL[1] ^ krrl; krr = subR[1] ^ krrr;
	CAMELLIA_F(kll, klr,
		   CAMELLIA_SIGMA1L, CAMELLIA_SIGMA1R,
		   w0, w1, il, ir, t0, t1);
	krl ^= w0; krr ^= w1;
	CAMELLIA_F(krl, krr,
		   CAMELLIA_SIGMA2L, CAMELLIA_SIGMA2R,
		   kll, klr, il, ir, t0, t1);
	kll ^= krll; klr ^= krlr;
	CAMELLIA_F(kll, klr,
		   CAMELLIA_SIGMA3L, CAMELLIA_SIGMA3R,
		   krl, krr, il, ir, t0, t1);
	krl ^= w0 ^ krrl; krr ^= w1 ^ krrr;
	CAMELLIA_F(krl, krr,
		   CAMELLIA_SIGMA4L, CAMELLIA_SIGMA4R,
		   w0, w1, il, ir, t0, t1);
	kll ^= w0; klr ^= w1;

	/* generate KB */
	krll ^= kll; krlr ^= klr;
	krrl ^= krl; krrr ^= krr;
	CAMELLIA_F(krll, krlr,
		   CAMELLIA_SIGMA5L, CAMELLIA_SIGMA5R,
		   w0, w1, il, ir, t0, t1);
	krrl ^= w0; krrr ^= w1;
	CAMELLIA_F(krrl, krrr,
		   CAMELLIA_SIGMA6L, CAMELLIA_SIGMA6R,
		   w0, w1, il, ir, t0, t1);
	krll ^= w0; krlr ^= w1;

	/* generate KA dependent subkeys */
	ROLDQ(kll, klr, krl, krr, w0, w1, 15);
	/* k5 */
	subL[6] = kll; subR[6] = klr;
	/* k6 */
	subL[7] = krl; subR[7] = krr;
	ROLDQ(kll, klr, krl, krr, w0, w1, 30);
	/* k11 */
	subL[14] = kll; subR[14] = klr;
	/* k12 */
	subL[15] = krl; subR[15] = krr;
	/* rotation left shift 32bit */
	/* kl5 */
	subL[24] = klr; subR[24] = krl;
	/* kl6 */
	subL[25] = krr; subR[25] = kll;
	/* rotation left shift 49 from k11,k12 -> k21,k22 */
	ROLDQo32(kll, klr, krl, krr, w0, w1, 49);
	/* k21 */
	subL[28] = kll; subR[28] = klr;
	/* k22 */
	subL[29] = krl; subR[29] = krr;

	/* generate KB dependent subkeys */
	/* k1 */
	subL[2] = krll; subR[2] = krlr;
	/* k2 */
	subL[3] = krrl; subR[3] = krrr;
	ROLDQ(krll, krlr, krrl, krrr, w0, w1, 30);
	/* k7 */
	subL[10] = krll; subR[10] = krlr;
	/* k8 */
	subL[11] = krrl; subR[11] = krrr;
	ROLDQ(krll, krlr, krrl, krrr, w0, w1, 30);
	/* k15 */
	subL[20] = krll; subR[20] = krlr;
	/* k16 */
	subL[21] = krrl; subR[21] = krrr;
	ROLDQo32(krll, krlr, krrl, krrr, w0, w1, 51);
	/* kw3 */
	subL[32] = krll; subR[32] = krlr;
	/* kw4 */
	subL[33] = krrl; subR[33] = krrr;

	camellia_setup_tail(subkey, subL, subR, 32);
}