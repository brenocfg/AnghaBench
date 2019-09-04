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
struct TYPE_10__ {int depth; int bpc; int nb_planes; int* planeheight; int* planewidth; int threshold; int peak; int planes; int nsteps; int** hlowsize; int** hhighsize; int** vlowsize; int** vhighsize; void* tmp; void* out; void* in; void* block; } ;
typedef  TYPE_3__ VagueDenoiserContext ;
struct TYPE_12__ {int h; int w; int /*<<< orphan*/  format; TYPE_1__* dst; } ;
struct TYPE_11__ {int nb_components; int /*<<< orphan*/  log2_chroma_w; int /*<<< orphan*/  log2_chroma_h; TYPE_2__* comp; } ;
struct TYPE_9__ {int depth; } ;
struct TYPE_8__ {TYPE_3__* priv; } ;
typedef  TYPE_4__ AVPixFmtDescriptor ;
typedef  TYPE_5__ AVFilterLink ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 void* AV_CEIL_RSHIFT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMAX (int,int) ; 
 int FFMIN (int,int) ; 
 void* av_malloc_array (int,int) ; 
 TYPE_4__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int pow (int,int) ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    VagueDenoiserContext *s = inlink->dst->priv;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);
    int p, i, nsteps_width, nsteps_height, nsteps_max;

    s->depth = desc->comp[0].depth;
    s->bpc = (s->depth + 7) / 8;
    s->nb_planes = desc->nb_components;

    s->planeheight[1] = s->planeheight[2] = AV_CEIL_RSHIFT(inlink->h, desc->log2_chroma_h);
    s->planeheight[0] = s->planeheight[3] = inlink->h;
    s->planewidth[1]  = s->planewidth[2]  = AV_CEIL_RSHIFT(inlink->w, desc->log2_chroma_w);
    s->planewidth[0]  = s->planewidth[3]  = inlink->w;

    s->block = av_malloc_array(inlink->w * inlink->h, sizeof(*s->block));
    s->in    = av_malloc_array(32 + FFMAX(inlink->w, inlink->h), sizeof(*s->in));
    s->out   = av_malloc_array(32 + FFMAX(inlink->w, inlink->h), sizeof(*s->out));
    s->tmp   = av_malloc_array(32 + FFMAX(inlink->w, inlink->h), sizeof(*s->tmp));

    if (!s->block || !s->in || !s->out || !s->tmp)
        return AVERROR(ENOMEM);

    s->threshold *= 1 << (s->depth - 8);
    s->peak = (1 << s->depth) - 1;

    nsteps_width  = ((s->planes & 2 || s->planes & 4) && s->nb_planes > 1) ? s->planewidth[1] : s->planewidth[0];
    nsteps_height = ((s->planes & 2 || s->planes & 4) && s->nb_planes > 1) ? s->planeheight[1] : s->planeheight[0];

    for (nsteps_max = 1; nsteps_max < 15; nsteps_max++) {
        if (pow(2, nsteps_max) >= nsteps_width || pow(2, nsteps_max) >= nsteps_height)
            break;
    }

    s->nsteps = FFMIN(s->nsteps, nsteps_max - 2);

    for (p = 0; p < 4; p++) {
        s->hlowsize[p][0]  = (s->planewidth[p] + 1) >> 1;
        s->hhighsize[p][0] =  s->planewidth[p] >> 1;
        s->vlowsize[p][0]  = (s->planeheight[p] + 1) >> 1;
        s->vhighsize[p][0] =  s->planeheight[p] >> 1;

        for (i = 1; i < s->nsteps; i++) {
            s->hlowsize[p][i]  = (s->hlowsize[p][i - 1] + 1) >> 1;
            s->hhighsize[p][i] =  s->hlowsize[p][i - 1] >> 1;
            s->vlowsize[p][i]  = (s->vlowsize[p][i - 1] + 1) >> 1;
            s->vhighsize[p][i] =  s->vlowsize[p][i - 1] >> 1;
        }
    }

    return 0;
}