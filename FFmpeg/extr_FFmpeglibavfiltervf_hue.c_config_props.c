#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ num; scalar_t__ den; } ;
struct TYPE_11__ {TYPE_6__ frame_rate; TYPE_6__ time_base; int /*<<< orphan*/  format; TYPE_1__* dst; } ;
struct TYPE_10__ {int /*<<< orphan*/  log2_chroma_h; int /*<<< orphan*/  log2_chroma_w; } ;
struct TYPE_9__ {void** var_values; int /*<<< orphan*/  vsub; int /*<<< orphan*/  hsub; } ;
struct TYPE_8__ {TYPE_2__* priv; } ;
typedef  TYPE_2__ HueContext ;
typedef  TYPE_3__ AVPixFmtDescriptor ;
typedef  TYPE_4__ AVFilterLink ;

/* Variables and functions */
 void* NAN ; 
 size_t VAR_N ; 
 size_t VAR_R ; 
 size_t VAR_TB ; 
 TYPE_3__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 void* av_q2d (TYPE_6__) ; 

__attribute__((used)) static int config_props(AVFilterLink *inlink)
{
    HueContext *hue = inlink->dst->priv;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);

    hue->hsub = desc->log2_chroma_w;
    hue->vsub = desc->log2_chroma_h;

    hue->var_values[VAR_N]  = 0;
    hue->var_values[VAR_TB] = av_q2d(inlink->time_base);
    hue->var_values[VAR_R]  = inlink->frame_rate.num == 0 || inlink->frame_rate.den == 0 ?
        NAN : av_q2d(inlink->frame_rate);

    return 0;
}