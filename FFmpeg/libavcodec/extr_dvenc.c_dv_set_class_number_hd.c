#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  void* int16_t ;
struct TYPE_3__ {int* area_q; int* sign; int* save; int* bit_size; int min_qlevel; scalar_t__ cno; void** mb; } ;
typedef  TYPE_1__ EncBlockInfo ;
typedef  int /*<<< orphan*/  DVVideoContext ;

/* Variables and functions */
 int FFABS (int) ; 

__attribute__((used)) static inline void dv_set_class_number_hd(DVVideoContext *s,
                                          int16_t *blk, EncBlockInfo *bi,
                                          const uint8_t *zigzag_scan,
                                          const int *weight, int bias)
{
    int i, max = 0;

    /* the first quantization (none at all) */
    bi->area_q[0] = 1;

    /* weigh AC components and store to save[] */
    /* (i=0 is the DC component; we only include it to make the
       number of loop iterations even, for future possible SIMD optimization) */
    for (i = 0; i < 64; i += 2) {
        int level0, level1;

        /* get the AC component (in zig-zag order) */
        level0 = blk[zigzag_scan[i+0]];
        level1 = blk[zigzag_scan[i+1]];

        /* extract sign and make it the lowest bit */
        bi->sign[i+0] = (level0>>31)&1;
        bi->sign[i+1] = (level1>>31)&1;

        /* take absolute value of the level */
        level0 = FFABS(level0);
        level1 = FFABS(level1);

        /* weigh it */
        level0 = (level0*weight[i+0] + 4096 + (1<<17)) >> 18;
        level1 = (level1*weight[i+1] + 4096 + (1<<17)) >> 18;

        /* save unquantized value */
        bi->save[i+0] = level0;
        bi->save[i+1] = level1;

         /* find max component */
        if (bi->save[i+0] > max)
            max = bi->save[i+0];
        if (bi->save[i+1] > max)
            max = bi->save[i+1];
    }

    /* copy DC component */
    bi->mb[0] = blk[0];

    /* the EOB code is 4 bits */
    bi->bit_size[0] = 4;
    bi->bit_size[1] = bi->bit_size[2] = bi->bit_size[3] = 0;

    /* ensure that no AC coefficients are cut off */
    bi->min_qlevel = ((max+256) >> 8);

    bi->area_q[0] = 25; /* set to an "impossible" value */
    bi->cno = 0;
}