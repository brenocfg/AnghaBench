#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {TYPE_2__ member_0; } ;
struct TYPE_10__ {TYPE_1__ member_0; } ;
typedef  TYPE_3__ DWTContext ;

/* Variables and functions */
 float FFABS (float) ; 
 int /*<<< orphan*/  FF_DWT97 ; 
 int MAX_W ; 
 int ff_dwt_decode (TYPE_3__*,float*) ; 
 int /*<<< orphan*/  ff_dwt_destroy (TYPE_3__*) ; 
 int ff_dwt_encode (TYPE_3__*,float*) ; 
 int ff_jpeg2000_dwt_init (TYPE_3__*,int**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int,int,double) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int test_dwtf(float *array, float *ref, int border[2][2], int decomp_levels, float max_diff) {
    int ret, j;
    DWTContext s1={{{0}}}, *s= &s1;
    double err2 = 0;

    ret = ff_jpeg2000_dwt_init(s,  border, decomp_levels, FF_DWT97);
    if (ret < 0) {
        fprintf(stderr, "ff_jpeg2000_dwt_init failed\n");
        return 1;
    }
    ret = ff_dwt_encode(s, array);
    if (ret < 0) {
        fprintf(stderr, "ff_dwt_encode failed\n");
        return 1;
    }
    ret = ff_dwt_decode(s, array);
    if (ret < 0) {
        fprintf(stderr, "ff_dwt_encode failed\n");
        return 1;
    }
    for (j = 0; j<MAX_W * MAX_W; j++) {
        if (FFABS(array[j] - ref[j]) > max_diff) {
            fprintf(stderr, "missmatch at %d (%f != %f) decomp:%d border %d %d %d %d\n",
                    j, array[j], ref[j],decomp_levels, border[0][0], border[0][1], border[1][0], border[1][1]);
            return 2;
        }
        err2 += (array[j] - ref[j]) * (array[j] - ref[j]);
        array[j] = ref[j];
    }
    ff_dwt_destroy(s);

    printf("9/7f, decomp:%2d border %3d %3d %3d %3d err2:%20.3f\n",
           decomp_levels, border[0][0], border[0][1], border[1][0], border[1][1],
           err2 / ((border[0][1] - border[0][0])*(border[1][1] - border[1][0])));

    return 0;
}