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
 int /*<<< orphan*/  CAMELLIA_F (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA1L ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA1R ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA2L ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA2R ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA3L ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA3R ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA4L ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA4R ; 
 int /*<<< orphan*/  ROLDQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ROLDQo32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  camellia_setup_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_unaligned_be32 (unsigned char const*) ; 

__attribute__((used)) static void camellia_setup128(const unsigned char *key, u32 *subkey)
{
	u32 kll, klr, krl, krr;
	u32 il, ir, t0, t1, w0, w1;
	u32 subL[26];
	u32 subR[26];

	/**
	 *  k == kll || klr || krl || krr (|| is concatenation)
	 */
	kll = get_unaligned_be32(key);
	klr = get_unaligned_be32(key + 4);
	krl = get_unaligned_be32(key + 8);
	krr = get_unaligned_be32(key + 12);

	/* generate KL dependent subkeys */
	/* kw1 */
	subL[0] = kll; subR[0] = klr;
	/* kw2 */
	subL[1] = krl; subR[1] = krr;
	/* rotation left shift 15bit */
	ROLDQ(kll, klr, krl, krr, w0, w1, 15);
	/* k3 */
	subL[4] = kll; subR[4] = klr;
	/* k4 */
	subL[5] = krl; subR[5] = krr;
	/* rotation left shift 15+30bit */
	ROLDQ(kll, klr, krl, krr, w0, w1, 30);
	/* k7 */
	subL[10] = kll; subR[10] = klr;
	/* k8 */
	subL[11] = krl; subR[11] = krr;
	/* rotation left shift 15+30+15bit */
	ROLDQ(kll, klr, krl, krr, w0, w1, 15);
	/* k10 */
	subL[13] = krl; subR[13] = krr;
	/* rotation left shift 15+30+15+17 bit */
	ROLDQ(kll, klr, krl, krr, w0, w1, 17);
	/* kl3 */
	subL[16] = kll; subR[16] = klr;
	/* kl4 */
	subL[17] = krl; subR[17] = krr;
	/* rotation left shift 15+30+15+17+17 bit */
	ROLDQ(kll, klr, krl, krr, w0, w1, 17);
	/* k13 */
	subL[18] = kll; subR[18] = klr;
	/* k14 */
	subL[19] = krl; subR[19] = krr;
	/* rotation left shift 15+30+15+17+17+17 bit */
	ROLDQ(kll, klr, krl, krr, w0, w1, 17);
	/* k17 */
	subL[22] = kll; subR[22] = klr;
	/* k18 */
	subL[23] = krl; subR[23] = krr;

	/* generate KA */
	kll = subL[0]; klr = subR[0];
	krl = subL[1]; krr = subR[1];
	CAMELLIA_F(kll, klr,
		   CAMELLIA_SIGMA1L, CAMELLIA_SIGMA1R,
		   w0, w1, il, ir, t0, t1);
	krl ^= w0; krr ^= w1;
	CAMELLIA_F(krl, krr,
		   CAMELLIA_SIGMA2L, CAMELLIA_SIGMA2R,
		   kll, klr, il, ir, t0, t1);
	/* current status == (kll, klr, w0, w1) */
	CAMELLIA_F(kll, klr,
		   CAMELLIA_SIGMA3L, CAMELLIA_SIGMA3R,
		   krl, krr, il, ir, t0, t1);
	krl ^= w0; krr ^= w1;
	CAMELLIA_F(krl, krr,
		   CAMELLIA_SIGMA4L, CAMELLIA_SIGMA4R,
		   w0, w1, il, ir, t0, t1);
	kll ^= w0; klr ^= w1;

	/* generate KA dependent subkeys */
	/* k1, k2 */
	subL[2] = kll; subR[2] = klr;
	subL[3] = krl; subR[3] = krr;
	ROLDQ(kll, klr, krl, krr, w0, w1, 15);
	/* k5,k6 */
	subL[6] = kll; subR[6] = klr;
	subL[7] = krl; subR[7] = krr;
	ROLDQ(kll, klr, krl, krr, w0, w1, 15);
	/* kl1, kl2 */
	subL[8] = kll; subR[8] = klr;
	subL[9] = krl; subR[9] = krr;
	ROLDQ(kll, klr, krl, krr, w0, w1, 15);
	/* k9 */
	subL[12] = kll; subR[12] = klr;
	ROLDQ(kll, klr, krl, krr, w0, w1, 15);
	/* k11, k12 */
	subL[14] = kll; subR[14] = klr;
	subL[15] = krl; subR[15] = krr;
	ROLDQo32(kll, klr, krl, krr, w0, w1, 34);
	/* k15, k16 */
	subL[20] = kll; subR[20] = klr;
	subL[21] = krl; subR[21] = krr;
	ROLDQ(kll, klr, krl, krr, w0, w1, 17);
	/* kw3, kw4 */
	subL[24] = kll; subR[24] = klr;
	subL[25] = krl; subR[25] = krr;

	camellia_setup_tail(subkey, subL, subR, 24);
}