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
typedef  int int64_t ;
typedef  int int16_t ;

/* Variables and functions */
 int LPC_ORDER ; 
 int MULL2 (int,int) ; 
 int av_clipl_int32 (int) ; 
 int av_sat_dadd32 (int,int) ; 
 int* cos_tab ; 

__attribute__((used)) static void lsp2lpc(int16_t *lpc)
{
    int f1[LPC_ORDER / 2 + 1];
    int f2[LPC_ORDER / 2 + 1];
    int i, j;

    /* Calculate negative cosine */
    for (j = 0; j < LPC_ORDER; j++) {
        int index     = (lpc[j] >> 7) & 0x1FF;
        int offset    = lpc[j] & 0x7f;
        int temp1     = cos_tab[index] * (1 << 16);
        int temp2     = (cos_tab[index + 1] - cos_tab[index]) *
                          (((offset << 8) + 0x80) << 1);

        lpc[j] = -(av_sat_dadd32(1 << 15, temp1 + temp2) >> 16);
    }

    /*
     * Compute sum and difference polynomial coefficients
     * (bitexact alternative to lsp2poly() in lsp.c)
     */
    /* Initialize with values in Q28 */
    f1[0] = 1 << 28;
    f1[1] = (lpc[0] + lpc[2]) * (1 << 14);
    f1[2] = lpc[0] * lpc[2] + (2 << 28);

    f2[0] = 1 << 28;
    f2[1] = (lpc[1] + lpc[3]) * (1 << 14);
    f2[2] = lpc[1] * lpc[3] + (2 << 28);

    /*
     * Calculate and scale the coefficients by 1/2 in
     * each iteration for a final scaling factor of Q25
     */
    for (i = 2; i < LPC_ORDER / 2; i++) {
        f1[i + 1] = av_clipl_int32(f1[i - 1] + (int64_t)MULL2(f1[i], lpc[2 * i]));
        f2[i + 1] = av_clipl_int32(f2[i - 1] + (int64_t)MULL2(f2[i], lpc[2 * i + 1]));

        for (j = i; j >= 2; j--) {
            f1[j] = MULL2(f1[j - 1], lpc[2 * i]) +
                    (f1[j] >> 1) + (f1[j - 2] >> 1);
            f2[j] = MULL2(f2[j - 1], lpc[2 * i + 1]) +
                    (f2[j] >> 1) + (f2[j - 2] >> 1);
        }

        f1[0] >>= 1;
        f2[0] >>= 1;
        f1[1] = ((lpc[2 * i]     * 65536 >> i) + f1[1]) >> 1;
        f2[1] = ((lpc[2 * i + 1] * 65536 >> i) + f2[1]) >> 1;
    }

    /* Convert polynomial coefficients to LPC coefficients */
    for (i = 0; i < LPC_ORDER / 2; i++) {
        int64_t ff1 = f1[i + 1] + f1[i];
        int64_t ff2 = f2[i + 1] - f2[i];

        lpc[i] = av_clipl_int32(((ff1 + ff2) * 8) + (1 << 15)) >> 16;
        lpc[LPC_ORDER - i - 1] = av_clipl_int32(((ff1 - ff2) * 8) +
                                                (1 << 15)) >> 16;
    }
}