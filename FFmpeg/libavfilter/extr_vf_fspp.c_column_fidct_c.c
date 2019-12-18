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
typedef  int int_simd16_t ;
typedef  int int16_t ;

/* Variables and functions */
 size_t DCTSIZE ; 
 int /*<<< orphan*/  FIX_0_382683433 ; 
 int /*<<< orphan*/  FIX_0_541196100 ; 
 int /*<<< orphan*/  FIX_0_707106781 ; 
 int /*<<< orphan*/  FIX_1_082392200 ; 
 int /*<<< orphan*/  FIX_1_306562965 ; 
 int /*<<< orphan*/  FIX_1_414213562 ; 
 int /*<<< orphan*/  FIX_1_414213562_A ; 
 int /*<<< orphan*/  FIX_1_847759065 ; 
 int /*<<< orphan*/  FIX_2_613125930 ; 
 int MULTIPLY16H (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THRESHOLD (int,int,int) ; 

__attribute__((used)) static void column_fidct_c(int16_t *thr_adr, int16_t *data, int16_t *output, int cnt)
{
    int_simd16_t tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
    int_simd16_t tmp10, tmp11, tmp12, tmp13;
    int_simd16_t z1,z2,z3,z4,z5, z10, z11, z12, z13;
    int_simd16_t d0, d1, d2, d3, d4, d5, d6, d7;

    int16_t *dataptr;
    int16_t *wsptr;
    int16_t *threshold;
    int ctr;

    dataptr = data;
    wsptr = output;

    for (; cnt > 0; cnt -= 2) { //start positions
        threshold = (int16_t *)thr_adr;//threshold_mtx
        for (ctr = DCTSIZE; ctr > 0; ctr--) {
            // Process columns from input, add to output.
            tmp0 = dataptr[DCTSIZE * 0] + dataptr[DCTSIZE * 7];
            tmp7 = dataptr[DCTSIZE * 0] - dataptr[DCTSIZE * 7];

            tmp1 = dataptr[DCTSIZE * 1] + dataptr[DCTSIZE * 6];
            tmp6 = dataptr[DCTSIZE * 1] - dataptr[DCTSIZE * 6];

            tmp2 = dataptr[DCTSIZE * 2] + dataptr[DCTSIZE * 5];
            tmp5 = dataptr[DCTSIZE * 2] - dataptr[DCTSIZE * 5];

            tmp3 = dataptr[DCTSIZE * 3] + dataptr[DCTSIZE * 4];
            tmp4 = dataptr[DCTSIZE * 3] - dataptr[DCTSIZE * 4];

            // Even part of FDCT

            tmp10 = tmp0 + tmp3;
            tmp13 = tmp0 - tmp3;
            tmp11 = tmp1 + tmp2;
            tmp12 = tmp1 - tmp2;

            d0 = tmp10 + tmp11;
            d4 = tmp10 - tmp11;

            z1 = MULTIPLY16H((tmp12 + tmp13) << 2, FIX_0_707106781);
            d2 = tmp13 + z1;
            d6 = tmp13 - z1;

            // Even part of IDCT

            THRESHOLD(tmp0, d0, threshold[0 * 8]);
            THRESHOLD(tmp1, d2, threshold[2 * 8]);
            THRESHOLD(tmp2, d4, threshold[4 * 8]);
            THRESHOLD(tmp3, d6, threshold[6 * 8]);
            tmp0 += 2;
            tmp10 = (tmp0 + tmp2) >> 2;
            tmp11 = (tmp0 - tmp2) >> 2;

            tmp13 = (tmp1 + tmp3) >>2; //+2 !  (psnr decides)
            tmp12 = MULTIPLY16H((tmp1 - tmp3), FIX_1_414213562_A) - tmp13; //<<2

            tmp0 = tmp10 + tmp13; //->temps
            tmp3 = tmp10 - tmp13; //->temps
            tmp1 = tmp11 + tmp12; //->temps
            tmp2 = tmp11 - tmp12; //->temps

            // Odd part of FDCT

            tmp10 = tmp4 + tmp5;
            tmp11 = tmp5 + tmp6;
            tmp12 = tmp6 + tmp7;

            z5 = MULTIPLY16H((tmp10 - tmp12) << 2, FIX_0_382683433);
            z2 = MULTIPLY16H(tmp10 << 2, FIX_0_541196100) + z5;
            z4 = MULTIPLY16H(tmp12 << 2, FIX_1_306562965) + z5;
            z3 = MULTIPLY16H(tmp11 << 2, FIX_0_707106781);

            z11 = tmp7 + z3;
            z13 = tmp7 - z3;

            d5 = z13 + z2;
            d3 = z13 - z2;
            d1 = z11 + z4;
            d7 = z11 - z4;

            // Odd part of IDCT

            THRESHOLD(tmp4, d1, threshold[1 * 8]);
            THRESHOLD(tmp5, d3, threshold[3 * 8]);
            THRESHOLD(tmp6, d5, threshold[5 * 8]);
            THRESHOLD(tmp7, d7, threshold[7 * 8]);

            //Simd version uses here a shortcut for the tmp5,tmp6,tmp7 == 0
            z13 = tmp6 + tmp5;
            z10 = (tmp6 - tmp5) << 1;
            z11 = tmp4 + tmp7;
            z12 = (tmp4 - tmp7) << 1;

            tmp7  = (z11 + z13) >> 2; //+2 !
            tmp11 = MULTIPLY16H((z11 - z13) << 1, FIX_1_414213562);
            z5    = MULTIPLY16H(z10 + z12,        FIX_1_847759065);
            tmp10 = MULTIPLY16H(z12,              FIX_1_082392200) - z5;
            tmp12 = MULTIPLY16H(z10,              FIX_2_613125930) + z5; // - !!

            tmp6 = tmp12 - tmp7;
            tmp5 = tmp11 - tmp6;
            tmp4 = tmp10 + tmp5;

            wsptr[DCTSIZE * 0] +=  (tmp0 + tmp7);
            wsptr[DCTSIZE * 1] +=  (tmp1 + tmp6);
            wsptr[DCTSIZE * 2] +=  (tmp2 + tmp5);
            wsptr[DCTSIZE * 3] +=  (tmp3 - tmp4);
            wsptr[DCTSIZE * 4] +=  (tmp3 + tmp4);
            wsptr[DCTSIZE * 5] +=  (tmp2 - tmp5);
            wsptr[DCTSIZE * 6]  =  (tmp1 - tmp6);
            wsptr[DCTSIZE * 7]  =  (tmp0 - tmp7);
            //
            dataptr++; //next column
            wsptr++;
            threshold++;
        }
        dataptr += 8; //skip each second start pos
        wsptr   += 8;
    }
}