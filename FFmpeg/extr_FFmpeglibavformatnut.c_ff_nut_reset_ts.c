#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_12__ {int num; int den; } ;
struct TYPE_11__ {TYPE_3__* stream; TYPE_2__* avf; } ;
struct TYPE_10__ {TYPE_1__* time_base; int /*<<< orphan*/  last_pts; } ;
struct TYPE_9__ {int nb_streams; } ;
struct TYPE_8__ {scalar_t__ num; scalar_t__ den; } ;
typedef  TYPE_4__ NUTContext ;
typedef  TYPE_5__ AVRational ;

/* Variables and functions */
 int /*<<< orphan*/  AV_ROUND_DOWN ; 
 int /*<<< orphan*/  av_rescale_rnd (int,int,int,int /*<<< orphan*/ ) ; 

void ff_nut_reset_ts(NUTContext *nut, AVRational time_base, int64_t val)
{
    int i;
    for (i = 0; i < nut->avf->nb_streams; i++)
        nut->stream[i].last_pts =
            av_rescale_rnd(val,
                           time_base.num * (int64_t)nut->stream[i].time_base->den,
                           time_base.den * (int64_t)nut->stream[i].time_base->num,
                           AV_ROUND_DOWN);
}