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
typedef  size_t ptrdiff_t ;
typedef  int int_simd16_t ;
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  DCTSIZE ; 
 int /*<<< orphan*/  FIX_0_382683433 ; 
 int /*<<< orphan*/  FIX_0_541196100 ; 
 int /*<<< orphan*/  FIX_0_707106781 ; 
 int /*<<< orphan*/  FIX_1_306562965 ; 
 int MULTIPLY16H (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void row_fdct_c(int16_t *data, const uint8_t *pixels, ptrdiff_t line_size, int cnt)
{
    int_simd16_t tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
    int_simd16_t tmp10, tmp11, tmp12, tmp13;
    int_simd16_t z1, z2, z3, z4, z5, z11, z13;
    int16_t *dataptr;

    cnt *= 4;
    // Pass 1: process rows.

    dataptr = data;
    for (; cnt > 0; cnt--) {
        tmp0 = pixels[line_size * 0] + pixels[line_size * 7];
        tmp7 = pixels[line_size * 0] - pixels[line_size * 7];
        tmp1 = pixels[line_size * 1] + pixels[line_size * 6];
        tmp6 = pixels[line_size * 1] - pixels[line_size * 6];
        tmp2 = pixels[line_size * 2] + pixels[line_size * 5];
        tmp5 = pixels[line_size * 2] - pixels[line_size * 5];
        tmp3 = pixels[line_size * 3] + pixels[line_size * 4];
        tmp4 = pixels[line_size * 3] - pixels[line_size * 4];

        // Even part

        tmp10 = tmp0 + tmp3;
        tmp13 = tmp0 - tmp3;
        tmp11 = tmp1 + tmp2;
        tmp12 = tmp1 - tmp2;
        //Even columns are written first, this leads to different order of columns
        //in column_fidct(), but they are processed independently, so all ok.
        //Later in the row_idct() columns readed at the same order.
        dataptr[2] = tmp10 + tmp11;
        dataptr[3] = tmp10 - tmp11;

        z1 = MULTIPLY16H((tmp12 + tmp13) << 2, FIX_0_707106781);
        dataptr[0] = tmp13 + z1;
        dataptr[1] = tmp13 - z1;

        // Odd part

        tmp10 = (tmp4 + tmp5) << 2;
        tmp11 = (tmp5 + tmp6) << 2;
        tmp12 = (tmp6 + tmp7) << 2;

        z5 = MULTIPLY16H(tmp10 - tmp12, FIX_0_382683433);
        z2 = MULTIPLY16H(tmp10,         FIX_0_541196100) + z5;
        z4 = MULTIPLY16H(tmp12,         FIX_1_306562965) + z5;
        z3 = MULTIPLY16H(tmp11,         FIX_0_707106781);

        z11 = tmp7 + z3;
        z13 = tmp7 - z3;

        dataptr[4] = z13 + z2;
        dataptr[5] = z13 - z2;
        dataptr[6] = z11 + z4;
        dataptr[7] = z11 - z4;

        pixels++;               // advance pointer to next column
        dataptr += DCTSIZE;
    }
}