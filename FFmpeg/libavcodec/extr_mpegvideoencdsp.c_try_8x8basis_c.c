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
typedef  int int16_t ;

/* Variables and functions */
 int BASIS_SHIFT ; 
 int RECON_SHIFT ; 
 int /*<<< orphan*/  av_assert2 (int) ; 

__attribute__((used)) static int try_8x8basis_c(int16_t rem[64], int16_t weight[64],
                          int16_t basis[64], int scale)
{
    int i;
    unsigned int sum = 0;

    for (i = 0; i < 8 * 8; i++) {
        int b = rem[i] + ((basis[i] * scale +
                           (1 << (BASIS_SHIFT - RECON_SHIFT - 1))) >>
                          (BASIS_SHIFT - RECON_SHIFT));
        int w = weight[i];
        b >>= RECON_SHIFT;
        av_assert2(-512 < b && b < 512);

        sum += (w * b) * (w * b) >> 4;
    }
    return sum >> 2;
}