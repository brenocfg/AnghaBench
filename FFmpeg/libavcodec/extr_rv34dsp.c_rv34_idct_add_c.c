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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  av_clip_uint8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rv34_row_transform (int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rv34_idct_add_c(uint8_t *dst, ptrdiff_t stride, int16_t *block){
    int      temp[16];
    int      i;

    rv34_row_transform(temp, block);
    memset(block, 0, 16*sizeof(int16_t));

    for(i = 0; i < 4; i++){
        const int z0 = 13*(temp[4*0+i] +    temp[4*2+i]) + 0x200;
        const int z1 = 13*(temp[4*0+i] -    temp[4*2+i]) + 0x200;
        const int z2 =  7* temp[4*1+i] - 17*temp[4*3+i];
        const int z3 = 17* temp[4*1+i] +  7*temp[4*3+i];

        dst[0] = av_clip_uint8( dst[0] + ( (z0 + z3) >> 10 ) );
        dst[1] = av_clip_uint8( dst[1] + ( (z1 + z2) >> 10 ) );
        dst[2] = av_clip_uint8( dst[2] + ( (z1 - z2) >> 10 ) );
        dst[3] = av_clip_uint8( dst[3] + ( (z0 - z3) >> 10 ) );

        dst  += stride;
    }
}