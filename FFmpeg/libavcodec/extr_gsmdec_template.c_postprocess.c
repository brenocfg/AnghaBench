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
 int av_clip_int16 (int) ; 
 int gsm_mult (int,int) ; 

__attribute__((used)) static int postprocess(int16_t *data, int msr)
{
    int i;
    for (i = 0; i < 160; i++) {
        msr = av_clip_int16(data[i] + gsm_mult(msr, 28180));
        data[i] = av_clip_int16(msr * 2) & ~7;
    }
    return msr;
}