#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ num; scalar_t__ den; } ;
struct TYPE_8__ {TYPE_5__ frame_rate; TYPE_1__* dst; } ;
struct TYPE_7__ {scalar_t__* var_values; } ;
struct TYPE_6__ {TYPE_2__* priv; } ;
typedef  TYPE_2__ EQContext ;
typedef  TYPE_3__ AVFilterLink ;

/* Variables and functions */
 scalar_t__ NAN ; 
 size_t VAR_N ; 
 size_t VAR_R ; 
 scalar_t__ av_q2d (TYPE_5__) ; 

__attribute__((used)) static int config_props(AVFilterLink *inlink)
{
    EQContext *eq = inlink->dst->priv;

    eq->var_values[VAR_N] = 0;
    eq->var_values[VAR_R] = inlink->frame_rate.num == 0 || inlink->frame_rate.den == 0 ?
        NAN : av_q2d(inlink->frame_rate);

    return 0;
}