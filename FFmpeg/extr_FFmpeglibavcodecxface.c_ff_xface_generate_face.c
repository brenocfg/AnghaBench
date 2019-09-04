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
 int XFACE_HEIGHT ; 
#define  XFACE_WIDTH 128 
 int* g_00 ; 
 int* g_01 ; 
 int* g_02 ; 
 int* g_10 ; 
 int* g_11 ; 
 int* g_12 ; 
 int* g_20 ; 
 int* g_21 ; 
 int* g_22 ; 
 int* g_30 ; 
 int* g_31 ; 
 int* g_32 ; 
 int* g_40 ; 
 int* g_41 ; 
 int* g_42 ; 

void ff_xface_generate_face(uint8_t *dst, uint8_t * const src)
{
    int h, i, j, k, l, m;

    for (j = 0; j < XFACE_HEIGHT; j++) {
        for (i = 0; i < XFACE_WIDTH; i++) {
            h = i + j * XFACE_WIDTH;
            k = 0;

            /*
               Compute k, encoding the bits *before* the current one, contained in the
               image buffer. That is, given the grid:

                l      i
                |      |
                v      v
               +--+--+--+--+--+
          m -> | 1| 2| 3| 4| 5|
               +--+--+--+--+--+
               | 6| 7| 8| 9|10|
               +--+--+--+--+--+
          j -> |11|12| *|  |  |
               +--+--+--+--+--+

               the value k for the pixel marked as "*" will contain the bit encoding of
               the values in the matrix marked from "1" to "12". In case the pixel is
               near the border of the grid, the number of values contained within the
               grid will be lesser than 12.
             */

            for (l = i - 2; l <= i + 2; l++) {
                for (m = j - 2; m <= j; m++) {
                    if (l <= 0 || l >= i && m == j)
                        continue;
                    if (l <= XFACE_WIDTH && m > 0)
                        k = 2*k + src[l + m * XFACE_WIDTH];
                }
            }

            /*
              Use the guess for the given position and the computed value of k.

              The following table shows the number of digits in k, depending on
              the position of the pixel, and shows the corresponding guess table
              to use:

                 i=1  i=2  i=3       i=w-1 i=w
               +----+----+----+ ... +----+----+
           j=1 |  0 |  1 |  2 |     |  2 |  2 |
               |g22 |g12 |g02 |     |g42 |g32 |
               +----+----+----+ ... +----+----+
           j=2 |  3 |  5 |  7 |     |  6 |  5 |
               |g21 |g11 |g01 |     |g41 |g31 |
               +----+----+----+ ... +----+----+
           j=3 |  5 |  9 | 12 |     | 10 |  8 |
               |g20 |g10 |g00 |     |g40 |g30 |
               +----+----+----+ ... +----+----+
            */

#define GEN(table) dst[h] ^= (table[k>>3]>>(7-(k&7)))&1

            switch (i) {
            case 1:
                switch (j) {
                case 1:  GEN(g_22); break;
                case 2:  GEN(g_21); break;
                default: GEN(g_20); break;
                }
                break;
            case 2:
                switch (j) {
                case 1:  GEN(g_12); break;
                case 2:  GEN(g_11); break;
                default: GEN(g_10); break;
                }
                break;
            case XFACE_WIDTH - 1:
                switch (j) {
                case 1:  GEN(g_42); break;
                case 2:  GEN(g_41); break;
                default: GEN(g_40); break;
                }
                break;
            case XFACE_WIDTH:
                switch (j) {
                case 1:  GEN(g_32); break;
                case 2:  GEN(g_31); break;
                default: GEN(g_30); break;
                }
                break;
            default:
                switch (j) {
                case 1:  GEN(g_02); break;
                case 2:  GEN(g_01); break;
                default: GEN(g_00); break;
                }
                break;
            }
        }
    }
}