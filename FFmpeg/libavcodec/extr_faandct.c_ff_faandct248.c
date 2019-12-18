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
typedef  int /*<<< orphan*/  int16_t ;
typedef  int FLOAT ;

/* Variables and functions */
 int A1 ; 
 int /*<<< orphan*/  emms_c () ; 
 int /*<<< orphan*/  lrintf (int) ; 
 int* postscale ; 
 int /*<<< orphan*/  row_fdct (int*,int /*<<< orphan*/ *) ; 

void ff_faandct248(int16_t *data)
{
    FLOAT tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
    FLOAT tmp10, tmp11, tmp12, tmp13;
    FLOAT temp[64];
    int i;

    emms_c();

    row_fdct(temp, data);

    for (i=0; i<8; i++) {
        tmp0 = temp[8*0 + i] + temp[8*1 + i];
        tmp1 = temp[8*2 + i] + temp[8*3 + i];
        tmp2 = temp[8*4 + i] + temp[8*5 + i];
        tmp3 = temp[8*6 + i] + temp[8*7 + i];
        tmp4 = temp[8*0 + i] - temp[8*1 + i];
        tmp5 = temp[8*2 + i] - temp[8*3 + i];
        tmp6 = temp[8*4 + i] - temp[8*5 + i];
        tmp7 = temp[8*6 + i] - temp[8*7 + i];

        tmp10 = tmp0 + tmp3;
        tmp11 = tmp1 + tmp2;
        tmp12 = tmp1 - tmp2;
        tmp13 = tmp0 - tmp3;

        data[8*0 + i] = lrintf(postscale[8*0 + i] * (tmp10 + tmp11));
        data[8*4 + i] = lrintf(postscale[8*4 + i] * (tmp10 - tmp11));

        tmp12 += tmp13;
        tmp12 *= A1;
        data[8*2 + i] = lrintf(postscale[8*2 + i] * (tmp13 + tmp12));
        data[8*6 + i] = lrintf(postscale[8*6 + i] * (tmp13 - tmp12));

        tmp10 = tmp4 + tmp7;
        tmp11 = tmp5 + tmp6;
        tmp12 = tmp5 - tmp6;
        tmp13 = tmp4 - tmp7;

        data[8*1 + i] = lrintf(postscale[8*0 + i] * (tmp10 + tmp11));
        data[8*5 + i] = lrintf(postscale[8*4 + i] * (tmp10 - tmp11));

        tmp12 += tmp13;
        tmp12 *= A1;
        data[8*3 + i] = lrintf(postscale[8*2 + i] * (tmp13 + tmp12));
        data[8*7 + i] = lrintf(postscale[8*6 + i] * (tmp13 - tmp12));
    }
}