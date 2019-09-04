#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {void* w; void* h; int /*<<< orphan*/  format; TYPE_1__* dst; } ;
struct TYPE_10__ {int /*<<< orphan*/  log2_chroma_w; int /*<<< orphan*/  log2_chroma_h; } ;
struct TYPE_9__ {int nb_planes; int* mode; int skip_odd; int skip_even; void** rg; void** planewidth; void** planeheight; } ;
struct TYPE_8__ {TYPE_2__* priv; } ;
typedef  TYPE_2__ RemoveGrainContext ;
typedef  TYPE_3__ AVPixFmtDescriptor ;
typedef  TYPE_4__ AVFilterLink ;

/* Variables and functions */
 scalar_t__ ARCH_X86 ; 
 void* AV_CEIL_RSHIFT (void*,int /*<<< orphan*/ ) ; 
 int av_pix_fmt_count_planes (int /*<<< orphan*/ ) ; 
 TYPE_3__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_removegrain_init_x86 (TYPE_2__*) ; 
 void* mode01 ; 
 void* mode02 ; 
 void* mode03 ; 
 void* mode04 ; 
 void* mode05 ; 
 void* mode06 ; 
 void* mode07 ; 
 void* mode08 ; 
 void* mode09 ; 
 void* mode10 ; 
 void* mode1112 ; 
 void* mode1314 ; 
 void* mode1516 ; 
 void* mode17 ; 
 void* mode18 ; 
 void* mode19 ; 
 void* mode20 ; 
 void* mode21 ; 
 void* mode22 ; 
 void* mode23 ; 
 void* mode24 ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    RemoveGrainContext *s = inlink->dst->priv;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);
    int i;

    s->nb_planes = av_pix_fmt_count_planes(inlink->format);

    s->planeheight[1] = s->planeheight[2] = AV_CEIL_RSHIFT(inlink->h, desc->log2_chroma_h);
    s->planeheight[0] = s->planeheight[3] = inlink->h;
    s->planewidth[1]  = s->planewidth[2]  = AV_CEIL_RSHIFT(inlink->w, desc->log2_chroma_w);
    s->planewidth[0]  = s->planewidth[3]  = inlink->w;

    for (i = 0; i < s->nb_planes; i++) {
        switch (s->mode[i]) {
        case 1:  s->rg[i] = mode01;   break;
        case 2:  s->rg[i] = mode02;   break;
        case 3:  s->rg[i] = mode03;   break;
        case 4:  s->rg[i] = mode04;   break;
        case 5:  s->rg[i] = mode05;   break;
        case 6:  s->rg[i] = mode06;   break;
        case 7:  s->rg[i] = mode07;   break;
        case 8:  s->rg[i] = mode08;   break;
        case 9:  s->rg[i] = mode09;   break;
        case 10: s->rg[i] = mode10;   break;
        case 11: s->rg[i] = mode1112; break;
        case 12: s->rg[i] = mode1112; break;
        case 13: s->skip_odd = 1;
                 s->rg[i] = mode1314; break;
        case 14: s->skip_even = 1;
                 s->rg[i] = mode1314; break;
        case 15: s->skip_odd = 1;
                 s->rg[i] = mode1516; break;
        case 16: s->skip_even = 1;
                 s->rg[i] = mode1516; break;
        case 17: s->rg[i] = mode17;   break;
        case 18: s->rg[i] = mode18;   break;
        case 19: s->rg[i] = mode19;   break;
        case 20: s->rg[i] = mode20;   break;
        case 21: s->rg[i] = mode21;   break;
        case 22: s->rg[i] = mode22;   break;
        case 23: s->rg[i] = mode23;   break;
        case 24: s->rg[i] = mode24;   break;
        }
    }

    if (ARCH_X86)
        ff_removegrain_init_x86(s);

    return 0;
}