#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {float* temp; } ;
typedef  TYPE_1__ On2AVCContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_on2avc_tab_10_1 ; 
 int /*<<< orphan*/  ff_on2avc_tab_10_2 ; 
 int /*<<< orphan*/  ff_on2avc_tab_20_1 ; 
 int /*<<< orphan*/  ff_on2avc_tab_20_2 ; 
 int /*<<< orphan*/  ff_on2avc_tab_40_1 ; 
 int /*<<< orphan*/  ff_on2avc_tab_40_2 ; 
 int /*<<< orphan*/  ff_on2avc_tab_84_1 ; 
 int /*<<< orphan*/  ff_on2avc_tab_84_2 ; 
 int /*<<< orphan*/  ff_on2avc_tab_84_3 ; 
 int /*<<< orphan*/  ff_on2avc_tab_84_4 ; 
 int /*<<< orphan*/  ff_on2avc_tabs_19_40_1 ; 
 int /*<<< orphan*/  ff_on2avc_tabs_19_40_2 ; 
 int /*<<< orphan*/  ff_on2avc_tabs_20_84_1 ; 
 int /*<<< orphan*/  ff_on2avc_tabs_20_84_2 ; 
 int /*<<< orphan*/  ff_on2avc_tabs_20_84_3 ; 
 int /*<<< orphan*/  ff_on2avc_tabs_20_84_4 ; 
 int /*<<< orphan*/  ff_on2avc_tabs_4_10_1 ; 
 int /*<<< orphan*/  ff_on2avc_tabs_4_10_2 ; 
 int /*<<< orphan*/  ff_on2avc_tabs_9_20_1 ; 
 int /*<<< orphan*/  ff_on2avc_tabs_9_20_2 ; 
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  twiddle (float*,float*,int,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wtf_end_1024 (TYPE_1__*,float*,float*,float*,float*) ; 
 int /*<<< orphan*/  wtf_end_512 (TYPE_1__*,float*,float*,float*,float*) ; 

__attribute__((used)) static void wtf_44(On2AVCContext *c, float *out, float *src, int size)
{
    float *tmp0 = c->temp, *tmp1 = c->temp + 1024;

    memset(tmp0, 0, sizeof(*tmp0) * 1024);
    memset(tmp1, 0, sizeof(*tmp1) * 1024);

    if (size == 512) {
        twiddle(src,       &tmp0[ 0], 16, ff_on2avc_tab_10_1, 10, 2, 1, 3, ff_on2avc_tabs_4_10_1);
        twiddle(src +   8, &tmp0[ 0], 16, ff_on2avc_tab_10_2, 10, 2, 3, 1, ff_on2avc_tabs_4_10_2);
        twiddle(src +  16, &tmp0[16], 16, ff_on2avc_tab_10_2, 10, 2, 3, 1, ff_on2avc_tabs_4_10_2);
        twiddle(src +  24, &tmp0[16], 16, ff_on2avc_tab_10_1, 10, 2, 1, 3, ff_on2avc_tabs_4_10_1);
        twiddle(src +  32, &tmp0[32], 16, ff_on2avc_tab_10_1, 10, 2, 1, 3, ff_on2avc_tabs_4_10_1);
        twiddle(src +  40, &tmp0[32], 16, ff_on2avc_tab_10_2, 10, 2, 3, 1, ff_on2avc_tabs_4_10_2);
        twiddle(src +  48, &tmp0[48], 16, ff_on2avc_tab_10_2, 10, 2, 3, 1, ff_on2avc_tabs_4_10_2);
        twiddle(src +  56, &tmp0[48], 16, ff_on2avc_tab_10_1, 10, 2, 1, 3, ff_on2avc_tabs_4_10_1);
        twiddle(&tmp0[ 0], &tmp1[ 0], 32, ff_on2avc_tab_20_1, 20, 2, 5, 4, ff_on2avc_tabs_9_20_1);
        twiddle(&tmp0[16], &tmp1[ 0], 32, ff_on2avc_tab_20_2, 20, 2, 4, 5, ff_on2avc_tabs_9_20_2);
        twiddle(&tmp0[32], &tmp1[32], 32, ff_on2avc_tab_20_2, 20, 2, 4, 5, ff_on2avc_tabs_9_20_2);
        twiddle(&tmp0[48], &tmp1[32], 32, ff_on2avc_tab_20_1, 20, 2, 5, 4, ff_on2avc_tabs_9_20_1);
        twiddle(src +  64, &tmp1[64], 32, ff_on2avc_tab_20_1, 20, 2, 5, 4, ff_on2avc_tabs_9_20_1);
        twiddle(src +  80, &tmp1[64], 32, ff_on2avc_tab_20_2, 20, 2, 4, 5, ff_on2avc_tabs_9_20_2);
        twiddle(src +  96, &tmp1[96], 32, ff_on2avc_tab_20_2, 20, 2, 4, 5, ff_on2avc_tabs_9_20_2);
        twiddle(src + 112, &tmp1[96], 32, ff_on2avc_tab_20_1, 20, 2, 5, 4, ff_on2avc_tabs_9_20_1);

        memset(tmp0, 0, 64 * sizeof(*tmp0));

        twiddle(&tmp1[ 0], &tmp0[  0], 128, ff_on2avc_tab_84_1, 84, 4, 16,  4, ff_on2avc_tabs_20_84_1);
        twiddle(&tmp1[32], &tmp0[  0], 128, ff_on2avc_tab_84_2, 84, 4, 16,  4, ff_on2avc_tabs_20_84_2);
        twiddle(&tmp1[64], &tmp0[  0], 128, ff_on2avc_tab_84_3, 84, 4, 13,  7, ff_on2avc_tabs_20_84_3);
        twiddle(&tmp1[96], &tmp0[  0], 128, ff_on2avc_tab_84_4, 84, 4, 15,  5, ff_on2avc_tabs_20_84_4);
        twiddle(src + 128, &tmp0[128], 128, ff_on2avc_tab_84_4, 84, 4, 15,  5, ff_on2avc_tabs_20_84_4);
        twiddle(src + 160, &tmp0[128], 128, ff_on2avc_tab_84_3, 84, 4, 13,  7, ff_on2avc_tabs_20_84_3);
        twiddle(src + 192, &tmp0[128], 128, ff_on2avc_tab_84_2, 84, 4, 16,  4, ff_on2avc_tabs_20_84_2);
        twiddle(src + 224, &tmp0[128], 128, ff_on2avc_tab_84_1, 84, 4, 16,  4, ff_on2avc_tabs_20_84_1);
        twiddle(src + 256, &tmp0[256], 128, ff_on2avc_tab_40_1, 40, 2, 11,  8, ff_on2avc_tabs_19_40_1);
        twiddle(src + 320, &tmp0[256], 128, ff_on2avc_tab_40_2, 40, 2,  8, 11, ff_on2avc_tabs_19_40_2);

        wtf_end_512(c, out, src, tmp0, tmp1);
    } else {
        twiddle(src,       &tmp0[  0], 32, ff_on2avc_tab_20_1, 20, 2,  5,  4, ff_on2avc_tabs_9_20_1);
        twiddle(src +  16, &tmp0[  0], 32, ff_on2avc_tab_20_2, 20, 2,  4,  5, ff_on2avc_tabs_9_20_2);
        twiddle(src +  32, &tmp0[ 32], 32, ff_on2avc_tab_20_2, 20, 2,  4,  5, ff_on2avc_tabs_9_20_2);
        twiddle(src +  48, &tmp0[ 32], 32, ff_on2avc_tab_20_1, 20, 2,  5,  4, ff_on2avc_tabs_9_20_1);
        twiddle(src +  64, &tmp0[ 64], 32, ff_on2avc_tab_20_1, 20, 2,  5,  4, ff_on2avc_tabs_9_20_1);
        twiddle(src +  80, &tmp0[ 64], 32, ff_on2avc_tab_20_2, 20, 2,  4,  5, ff_on2avc_tabs_9_20_2);
        twiddle(src +  96, &tmp0[ 96], 32, ff_on2avc_tab_20_2, 20, 2,  4,  5, ff_on2avc_tabs_9_20_2);
        twiddle(src + 112, &tmp0[ 96], 32, ff_on2avc_tab_20_1, 20, 2,  5,  4, ff_on2avc_tabs_9_20_1);
        twiddle(&tmp0[ 0], &tmp1[  0], 64, ff_on2avc_tab_40_1, 40, 2, 11,  8, ff_on2avc_tabs_19_40_1);
        twiddle(&tmp0[32], &tmp1[  0], 64, ff_on2avc_tab_40_2, 40, 2,  8, 11, ff_on2avc_tabs_19_40_2);
        twiddle(&tmp0[64], &tmp1[ 64], 64, ff_on2avc_tab_40_2, 40, 2,  8, 11, ff_on2avc_tabs_19_40_2);
        twiddle(&tmp0[96], &tmp1[ 64], 64, ff_on2avc_tab_40_1, 40, 2, 11,  8, ff_on2avc_tabs_19_40_1);
        twiddle(src + 128, &tmp1[128], 64, ff_on2avc_tab_40_1, 40, 2, 11,  8, ff_on2avc_tabs_19_40_1);
        twiddle(src + 160, &tmp1[128], 64, ff_on2avc_tab_40_2, 40, 2,  8, 11, ff_on2avc_tabs_19_40_2);
        twiddle(src + 192, &tmp1[192], 64, ff_on2avc_tab_40_2, 40, 2,  8, 11, ff_on2avc_tabs_19_40_2);
        twiddle(src + 224, &tmp1[192], 64, ff_on2avc_tab_40_1, 40, 2, 11,  8, ff_on2avc_tabs_19_40_1);

        memset(tmp0, 0, 128 * sizeof(*tmp0));

        twiddle(&tmp1[  0], &tmp0[  0], 256, ff_on2avc_tab_84_1, 84, 4, 16,  4, ff_on2avc_tabs_20_84_1);
        twiddle(&tmp1[ 64], &tmp0[  0], 256, ff_on2avc_tab_84_2, 84, 4, 16,  4, ff_on2avc_tabs_20_84_2);
        twiddle(&tmp1[128], &tmp0[  0], 256, ff_on2avc_tab_84_3, 84, 4, 13,  7, ff_on2avc_tabs_20_84_3);
        twiddle(&tmp1[192], &tmp0[  0], 256, ff_on2avc_tab_84_4, 84, 4, 15,  5, ff_on2avc_tabs_20_84_4);
        twiddle(src + 256,  &tmp0[256], 256, ff_on2avc_tab_84_4, 84, 4, 15,  5, ff_on2avc_tabs_20_84_4);
        twiddle(src + 320,  &tmp0[256], 256, ff_on2avc_tab_84_3, 84, 4, 13,  7, ff_on2avc_tabs_20_84_3);
        twiddle(src + 384,  &tmp0[256], 256, ff_on2avc_tab_84_2, 84, 4, 16,  4, ff_on2avc_tabs_20_84_2);
        twiddle(src + 448,  &tmp0[256], 256, ff_on2avc_tab_84_1, 84, 4, 16,  4, ff_on2avc_tabs_20_84_1);
        twiddle(src + 512,  &tmp0[512], 256, ff_on2avc_tab_40_1, 40, 2, 11,  8, ff_on2avc_tabs_19_40_1);
        twiddle(src + 640,  &tmp0[512], 256, ff_on2avc_tab_40_2, 40, 2,  8, 11, ff_on2avc_tabs_19_40_2);

        wtf_end_1024(c, out, src, tmp0, tmp1);
    }
}