#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int** direct_scale_mv; int pb_time; int pp_time; } ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */
 int tab_bias ; 
 int tab_size ; 

void ff_mpeg4_init_direct_mv(MpegEncContext *s)
{
    int i;
    for (i = 0; i < tab_size; i++) {
        s->direct_scale_mv[0][i] = (i - tab_bias) * s->pb_time / s->pp_time;
        s->direct_scale_mv[1][i] = (i - tab_bias) * (s->pb_time - s->pp_time) /
                                   s->pp_time;
    }
}