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
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */
 int FFMAX (int,int) ; 
 int FFMIN (int,int) ; 
 int area1 ; 
 int area2 ; 
 int area3 ; 
 int area4 ; 
 int area5 ; 
 int area6 ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 

__attribute__((used)) static void x8_setup_spatial_compensation(uint8_t *src, uint8_t *dst,
                                          ptrdiff_t stride, int *range,
                                          int *psum, int edges)
{
    uint8_t *ptr;
    int sum;
    int i;
    int min_pix, max_pix;
    uint8_t c;

    if ((edges & 3) == 3) {
        *psum  = 0x80 * (8 + 1 + 8 + 2);
        *range = 0;
        memset(dst, 0x80, 16 + 1 + 16 + 8);
        /* this triggers flat_dc for sure. flat_dc avoids all (other)
         * prediction modes, but requires dc_level decoding. */
        return;
    }

    min_pix = 256;
    max_pix = -1;

    sum = 0;

    if (!(edges & 1)) { // (mb_x != 0) // there is previous block on this row
        ptr = src - 1; // left column, area 2
        for (i = 7; i >= 0; i--) {
            c              = *(ptr - 1); // area1, same mb as area2, no need to check
            dst[area1 + i] = c;
            c              = *ptr;

            sum           += c;
            min_pix        = FFMIN(min_pix, c);
            max_pix        = FFMAX(max_pix, c);
            dst[area2 + i] = c;

            ptr += stride;
        }
    }

    if (!(edges & 2)) { // (mb_y != 0) // there is row above
        ptr = src - stride; // top line
        for (i = 0; i < 8; i++) {
            c       = *(ptr + i);
            sum    += c;
            min_pix = FFMIN(min_pix, c);
            max_pix = FFMAX(max_pix, c);
        }
        if (edges & 4) { // last block on the row?
            memset(dst + area5, c, 8); // set with last pixel fr
            memcpy(dst + area4, ptr, 8);
        } else {
            memcpy(dst + area4, ptr, 16); // both area4 and 5
        }
        // area6 always present in the above block
        memcpy(dst + area6, ptr - stride, 8);
    }
    // now calculate the stuff we need
    if (edges & 3) { // mb_x ==0 || mb_y == 0) {
        int avg = (sum + 4) >> 3;

        if (edges & 1) // (mb_x == 0) { // implies mb_y !=0
            memset(dst + area1, avg, 8 + 8 + 1); // areas 1, 2, 3 are averaged
        else // implies y == 0 x != 0
            memset(dst + area3, avg, 1 + 16 + 8); // areas 3, 4, 5, 6

        sum += avg * 9;
    } else {
        // the edge pixel, in the top line and left column
        uint8_t c = *(src - 1 - stride);
        dst[area3] = c;
        sum       += c;
        // edge pixel is not part of min/max
    }
    *range = max_pix - min_pix;
    sum   += *(dst + area5) + *(dst + area5 + 1);
    *psum  = sum;
}