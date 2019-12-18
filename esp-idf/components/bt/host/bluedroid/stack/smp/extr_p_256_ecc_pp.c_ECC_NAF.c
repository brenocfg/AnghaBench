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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int DWORD ;

/* Variables and functions */
 int multiprecision_most_signbits (int*,int) ; 
 int /*<<< orphan*/  multiprecision_rshift (int*,int*,int) ; 

__attribute__((used)) static void ECC_NAF(uint8_t *naf, uint32_t *NumNAF, DWORD *k, uint32_t keyLength)
{
    uint32_t sign;
    int i = 0;
    int j;
    uint32_t var;

    while ((var = multiprecision_most_signbits(k, keyLength)) >= 1) {
        if (k[0] & 0x01) { // k is odd
            sign = (k[0] & 0x03);  // 1 or 3

            // k = k-naf[i]
            if (sign == 1) {
                k[0] = k[0] & 0xFFFFFFFE;
            } else {
                k[0] = k[0] + 1;
                if (k[0] == 0) { //overflow
                    j = 1;
                    do {
                        k[j]++;
                    } while (k[j++] == 0); //overflow
                }
            }
        } else {
            sign = 0;
        }

        multiprecision_rshift(k, k, keyLength);
        naf[i / 4] |= (sign) << ((i % 4) * 2);
        i++;
    }

    *NumNAF = i;
}