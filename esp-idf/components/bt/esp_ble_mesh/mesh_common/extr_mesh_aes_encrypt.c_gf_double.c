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

/* Variables and functions */
 int TC_AES_BLOCK_SIZE ; 
 int gf_wrap ; 

void gf_double(uint8_t *out, uint8_t *in)
{

    /* start with low order byte */
    uint8_t *x = in + (TC_AES_BLOCK_SIZE - 1);

    /* if msb == 1, we need to add the gf_wrap value, otherwise add 0 */
    uint8_t carry = (in[0] >> 7) ? gf_wrap : 0;

    out += (TC_AES_BLOCK_SIZE - 1);
    for (;;) {
        *out-- = (*x << 1) ^ carry;
        if (x == in) {
            break;
        }
        carry = *x-- >> 7;
    }
}