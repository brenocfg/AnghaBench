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
 int /*<<< orphan*/  rv34_row_transform (int*,int*) ; 

__attribute__((used)) static void rv34_inv_transform_noround_c(int16_t *block){
    int temp[16];
    int i;

    rv34_row_transform(temp, block);

    for(i = 0; i < 4; i++){
        const int z0 = 39*(temp[4*0+i] +    temp[4*2+i]);
        const int z1 = 39*(temp[4*0+i] -    temp[4*2+i]);
        const int z2 = 21* temp[4*1+i] - 51*temp[4*3+i];
        const int z3 = 51* temp[4*1+i] + 21*temp[4*3+i];

        block[i*4+0] = (z0 + z3) >> 11;
        block[i*4+1] = (z1 + z2) >> 11;
        block[i*4+2] = (z1 - z2) >> 11;
        block[i*4+3] = (z0 - z3) >> 11;
    }
}