#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_3__* HEVClc; } ;
struct TYPE_10__ {void* y; void* x; } ;
struct TYPE_11__ {TYPE_1__ mvd; } ;
struct TYPE_12__ {TYPE_2__ pu; } ;
typedef  TYPE_3__ HEVCLocalContext ;
typedef  TYPE_4__ HEVCContext ;

/* Variables and functions */
 int abs_mvd_greater0_flag_decode (TYPE_4__*) ; 
 scalar_t__ abs_mvd_greater1_flag_decode (TYPE_4__*) ; 
 void* mvd_decode (TYPE_4__*) ; 
 void* mvd_sign_flag_decode (TYPE_4__*) ; 

void ff_hevc_hls_mvd_coding(HEVCContext *s, int x0, int y0, int log2_cb_size)
{
    HEVCLocalContext *lc = s->HEVClc;
    int x = abs_mvd_greater0_flag_decode(s);
    int y = abs_mvd_greater0_flag_decode(s);

    if (x)
        x += abs_mvd_greater1_flag_decode(s);
    if (y)
        y += abs_mvd_greater1_flag_decode(s);

    switch (x) {
    case 2: lc->pu.mvd.x = mvd_decode(s);           break;
    case 1: lc->pu.mvd.x = mvd_sign_flag_decode(s); break;
    case 0: lc->pu.mvd.x = 0;                       break;
    }

    switch (y) {
    case 2: lc->pu.mvd.y = mvd_decode(s);           break;
    case 1: lc->pu.mvd.y = mvd_sign_flag_decode(s); break;
    case 0: lc->pu.mvd.y = 0;                       break;
    }
}