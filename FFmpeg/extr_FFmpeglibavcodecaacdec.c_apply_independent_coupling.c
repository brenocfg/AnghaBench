#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_3__* oc; } ;
struct TYPE_14__ {float** gain; } ;
struct TYPE_16__ {TYPE_1__* ch; TYPE_4__ coup; } ;
struct TYPE_15__ {float* ret; } ;
struct TYPE_12__ {int sbr; } ;
struct TYPE_13__ {TYPE_2__ m4ac; } ;
struct TYPE_11__ {float* ret; } ;
typedef  TYPE_5__ SingleChannelElement ;
typedef  TYPE_6__ ChannelElement ;
typedef  TYPE_7__ AACContext ;

/* Variables and functions */

__attribute__((used)) static void apply_independent_coupling(AACContext *ac,
                                       SingleChannelElement *target,
                                       ChannelElement *cce, int index)
{
    int i;
    const float gain = cce->coup.gain[index][0];
    const float *src = cce->ch[0].ret;
    float *dest = target->ret;
    const int len = 1024 << (ac->oc[1].m4ac.sbr == 1);

    for (i = 0; i < len; i++)
        dest[i] += gain * src[i];
}