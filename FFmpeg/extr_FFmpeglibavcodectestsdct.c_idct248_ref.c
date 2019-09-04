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
typedef  int ptrdiff_t ;
typedef  double int16_t ;

/* Variables and functions */
 int M_PI ; 
 double cos (int) ; 
 scalar_t__ rint (double) ; 
 double sqrt (double) ; 

__attribute__((used)) static void idct248_ref(uint8_t *dest, ptrdiff_t linesize, int16_t *block)
{
    static int init;
    static double c8[8][8];
    static double c4[4][4];
    double block1[64], block2[64], block3[64];
    double s, sum, v;
    int i, j, k;

    if (!init) {
        init = 1;

        for (i = 0; i < 8; i++) {
            sum = 0;
            for (j = 0; j < 8; j++) {
                s = (i == 0) ? sqrt(1.0 / 8.0) : sqrt(1.0 / 4.0);
                c8[i][j] = s * cos(M_PI * i * (j + 0.5) / 8.0);
                sum += c8[i][j] * c8[i][j];
            }
        }

        for (i = 0; i < 4; i++) {
            sum = 0;
            for (j = 0; j < 4; j++) {
                s = (i == 0) ? sqrt(1.0 / 4.0) : sqrt(1.0 / 2.0);
                c4[i][j] = s * cos(M_PI * i * (j + 0.5) / 4.0);
                sum += c4[i][j] * c4[i][j];
            }
        }
    }

    /* butterfly */
    s = 0.5 * sqrt(2.0);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 8; j++) {
            block1[8 * (2 * i) + j] =
                (block[8 * (2 * i) + j] + block[8 * (2 * i + 1) + j]) * s;
            block1[8 * (2 * i + 1) + j] =
                (block[8 * (2 * i) + j] - block[8 * (2 * i + 1) + j]) * s;
        }
    }

    /* idct8 on lines */
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            sum = 0;
            for (k = 0; k < 8; k++)
                sum += c8[k][j] * block1[8 * i + k];
            block2[8 * i + j] = sum;
        }
    }

    /* idct4 */
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 4; j++) {
            /* top */
            sum = 0;
            for (k = 0; k < 4; k++)
                sum += c4[k][j] * block2[8 * (2 * k) + i];
            block3[8 * (2 * j) + i] = sum;

            /* bottom */
            sum = 0;
            for (k = 0; k < 4; k++)
                sum += c4[k][j] * block2[8 * (2 * k + 1) + i];
            block3[8 * (2 * j + 1) + i] = sum;
        }
    }

    /* clamp and store the result */
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            v = block3[8 * i + j];
            if      (v < 0)   v = 0;
            else if (v > 255) v = 255;
            dest[i * linesize + j] = (int) rint(v);
        }
    }
}