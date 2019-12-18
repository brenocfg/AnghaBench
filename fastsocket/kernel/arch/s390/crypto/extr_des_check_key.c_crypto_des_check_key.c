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
typedef  size_t u8 ;
typedef  int u32 ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_WEAK_KEY ; 
 int CRYPTO_TFM_RES_WEAK_KEY ; 
 int EINVAL ; 
 int* parity ; 

int
crypto_des_check_key(const u8 *key, unsigned int keylen, u32 *flags)
{
	u32 n, w;

	n  = parity[key[0]]; n <<= 4;
	n |= parity[key[1]]; n <<= 4;
	n |= parity[key[2]]; n <<= 4;
	n |= parity[key[3]]; n <<= 4;
	n |= parity[key[4]]; n <<= 4;
	n |= parity[key[5]]; n <<= 4;
	n |= parity[key[6]]; n <<= 4;
	n |= parity[key[7]];
	w = 0x88888888L;

	if ((*flags & CRYPTO_TFM_REQ_WEAK_KEY)
	    && !((n - (w >> 3)) & w)) {  /* 1 in 10^10 keys passes this test */
		if (n < 0x41415151) {
			if (n < 0x31312121) {
				if (n < 0x14141515) {
					/* 01 01 01 01 01 01 01 01 */
					if (n == 0x11111111) goto weak;
					/* 01 1F 01 1F 01 0E 01 0E */
					if (n == 0x13131212) goto weak;
				} else {
					/* 01 E0 01 E0 01 F1 01 F1 */
					if (n == 0x14141515) goto weak;
					/* 01 FE 01 FE 01 FE 01 FE */
					if (n == 0x16161616) goto weak;
				}
			} else {
				if (n < 0x34342525) {
					/* 1F 01 1F 01 0E 01 0E 01 */
					if (n == 0x31312121) goto weak;
					/* 1F 1F 1F 1F 0E 0E 0E 0E (?) */
					if (n == 0x33332222) goto weak;
				} else {
					/* 1F E0 1F E0 0E F1 0E F1 */
					if (n == 0x34342525) goto weak;
					/* 1F FE 1F FE 0E FE 0E FE */
					if (n == 0x36362626) goto weak;
				}
			}
		} else {
			if (n < 0x61616161) {
				if (n < 0x44445555) {
					/* E0 01 E0 01 F1 01 F1 01 */
					if (n == 0x41415151) goto weak;
					/* E0 1F E0 1F F1 0E F1 0E */
					if (n == 0x43435252) goto weak;
				} else {
					/* E0 E0 E0 E0 F1 F1 F1 F1 (?) */
					if (n == 0x44445555) goto weak;
					/* E0 FE E0 FE F1 FE F1 FE */
					if (n == 0x46465656) goto weak;
				}
			} else {
				if (n < 0x64646565) {
					/* FE 01 FE 01 FE 01 FE 01 */
					if (n == 0x61616161) goto weak;
					/* FE 1F FE 1F FE 0E FE 0E */
					if (n == 0x63636262) goto weak;
				} else {
					/* FE E0 FE E0 FE F1 FE F1 */
					if (n == 0x64646565) goto weak;
					/* FE FE FE FE FE FE FE FE */
					if (n == 0x66666666) goto weak;
				}
			}
		}
	}
	return 0;
weak:
	*flags |= CRYPTO_TFM_RES_WEAK_KEY;
	return -EINVAL;
}