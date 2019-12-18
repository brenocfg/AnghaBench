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
 int A2 ; 
 int A4 ; 
 int A5 ; 
 int /*<<< orphan*/  emms_c () ; 
 int /*<<< orphan*/  lrintf (int) ; 
 int* postscale ; 
 int /*<<< orphan*/  row_fdct (int*,int /*<<< orphan*/ *) ; 

void ff_faandct(int16_t *data)
{
    FLOAT tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
    FLOAT tmp10, tmp11, tmp12, tmp13;
    FLOAT z2, z4, z11, z13;
    FLOAT temp[64];
    int i;

    emms_c();

    row_fdct(temp, data);

    for (i=0; i<8; i++) {
        tmp0= temp[8*0 + i] + temp[8*7 + i];
        tmp7= temp[8*0 + i] - temp[8*7 + i];
        tmp1= temp[8*1 + i] + temp[8*6 + i];
        tmp6= temp[8*1 + i] - temp[8*6 + i];
        tmp2= temp[8*2 + i] + temp[8*5 + i];
        tmp5= temp[8*2 + i] - temp[8*5 + i];
        tmp3= temp[8*3 + i] + temp[8*4 + i];
        tmp4= temp[8*3 + i] - temp[8*4 + i];

        tmp10= tmp0 + tmp3;
        tmp13= tmp0 - tmp3;
        tmp11= tmp1 + tmp2;
        tmp12= tmp1 - tmp2;

        data[8*0 + i]= lrintf(postscale[8*0 + i] * (tmp10 + tmp11));
        data[8*4 + i]= lrintf(postscale[8*4 + i] * (tmp10 - tmp11));

        tmp12 += tmp13;
        tmp12 *= A1;
        data[8*2 + i]= lrintf(postscale[8*2 + i] * (tmp13 + tmp12));
        data[8*6 + i]= lrintf(postscale[8*6 + i] * (tmp13 - tmp12));

        tmp4 += tmp5;
        tmp5 += tmp6;
        tmp6 += tmp7;

        z2= tmp4*(A2+A5) - tmp6*A5;
        z4= tmp6*(A4-A5) + tmp4*A5;

        tmp5*=A1;

        z11= tmp7 + tmp5;
        z13= tmp7 - tmp5;

        data[8*5 + i]= lrintf(postscale[8*5 + i] * (z13 + z2));
        data[8*3 + i]= lrintf(postscale[8*3 + i] * (z13 - z2));
        data[8*1 + i]= lrintf(postscale[8*1 + i] * (z11 + z4));
        data[8*7 + i]= lrintf(postscale[8*7 + i] * (z11 - z4));
    }
}