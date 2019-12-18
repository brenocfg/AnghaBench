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
typedef  int int64_t ;

/* Variables and functions */
 int* costbl_12 ; 
 int* costbl_4 ; 
 int* costbl_8 ; 
 int* sintbl_12 ; 
 int* sintbl_4 ; 
 int* sintbl_8 ; 

__attribute__((used)) static void make_filters_from_proto(int (*filter)[8][2], const int *proto, int bands)
{

    const int *sinptr, *cosptr;
    int s, c, sinhalf, coshalf;
    int q, n;

    if (bands == 4) {
        sinptr = sintbl_4;
        cosptr = costbl_4;
        sinhalf = 759250125;
        coshalf = 759250125;
    } else if (bands == 8) {
        sinptr = sintbl_8;
        cosptr = costbl_8;
        sinhalf = 410903207;
        coshalf = 992008094;
    } else {
        sinptr = sintbl_12;
        cosptr = costbl_12;
        sinhalf = 277904834;
        coshalf = 1037154959;
    }

    for (q = 0; q < bands; q++) {
        for (n = 0; n < 7; n++) {
            int theta = (q*(n-6) + (n>>1) - 3) % bands;

            if (theta < 0)
                theta += bands;
            s = sinptr[theta];
            c = cosptr[theta];

            if (n & 1) {
                theta = (int)(((int64_t)c * coshalf - (int64_t)s * sinhalf + 0x20000000) >> 30);
                s = (int)(((int64_t)s * coshalf + (int64_t)c * sinhalf + 0x20000000) >> 30);
                c = theta;
            }
            filter[q][n][0] = (int)(((int64_t)proto[n] * c + 0x20000000) >> 30);
            filter[q][n][1] = -(int)(((int64_t)proto[n] * s + 0x20000000) >> 30);
        }
    }
}