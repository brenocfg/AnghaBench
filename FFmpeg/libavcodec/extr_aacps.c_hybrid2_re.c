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
typedef  int INTFLOAT ;
typedef  int INT64FLOAT ;

/* Variables and functions */
 int AAC_MUL31 (int const,int) ; 

__attribute__((used)) static void hybrid2_re(INTFLOAT (*in)[2], INTFLOAT (*out)[32][2], const INTFLOAT filter[8], int len, int reverse)
{
    int i, j;
    for (i = 0; i < len; i++, in++) {
        INT64FLOAT re_in = AAC_MUL31(filter[6], in[6][0]); //real inphase
        INT64FLOAT re_op = 0.0f;                          //real out of phase
        INT64FLOAT im_in = AAC_MUL31(filter[6], in[6][1]); //imag inphase
        INT64FLOAT im_op = 0.0f;                          //imag out of phase
        for (j = 0; j < 6; j += 2) {
            re_op += (INT64FLOAT)filter[j+1] * (in[j+1][0] + in[12-j-1][0]);
            im_op += (INT64FLOAT)filter[j+1] * (in[j+1][1] + in[12-j-1][1]);
        }

#if USE_FIXED
        re_op = (re_op + 0x40000000) >> 31;
        im_op = (im_op + 0x40000000) >> 31;
#endif /* USE_FIXED */

        out[ reverse][i][0] = (INTFLOAT)(re_in + re_op);
        out[ reverse][i][1] = (INTFLOAT)(im_in + im_op);
        out[!reverse][i][0] = (INTFLOAT)(re_in - re_op);
        out[!reverse][i][1] = (INTFLOAT)(im_in - im_op);
    }
}