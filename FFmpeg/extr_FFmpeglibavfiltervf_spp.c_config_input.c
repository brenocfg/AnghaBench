#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int h; int w; int /*<<< orphan*/  format; TYPE_1__* dst; } ;
struct TYPE_12__ {int /*<<< orphan*/  log2_chroma_h; int /*<<< orphan*/  log2_chroma_w; TYPE_2__* comp; } ;
struct TYPE_11__ {void* src; void* temp; void* temp_linesize; int /*<<< orphan*/  vsub; int /*<<< orphan*/  hsub; int /*<<< orphan*/  dct; } ;
struct TYPE_10__ {int depth; } ;
struct TYPE_9__ {TYPE_3__* priv; } ;
typedef  TYPE_3__ SPPContext ;
typedef  TYPE_4__ AVPixFmtDescriptor ;
typedef  TYPE_5__ AVFilterLink ;

/* Variables and functions */
 scalar_t__ ARCH_X86 ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* FFALIGN (int,int) ; 
 void* av_malloc_array (void*,int const) ; 
 int /*<<< orphan*/  av_opt_set_int (int /*<<< orphan*/ ,char*,int const,int /*<<< orphan*/ ) ; 
 TYPE_4__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avcodec_dct_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_spp_init_x86 (TYPE_3__*) ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    SPPContext *s = inlink->dst->priv;
    const int h = FFALIGN(inlink->h + 16, 16);
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);
    const int bps = desc->comp[0].depth;

    av_opt_set_int(s->dct, "bits_per_sample", bps, 0);
    avcodec_dct_init(s->dct);

    if (ARCH_X86)
        ff_spp_init_x86(s);

    s->hsub = desc->log2_chroma_w;
    s->vsub = desc->log2_chroma_h;
    s->temp_linesize = FFALIGN(inlink->w + 16, 16);
    s->temp = av_malloc_array(s->temp_linesize, h * sizeof(*s->temp));
    s->src  = av_malloc_array(s->temp_linesize, h * sizeof(*s->src) * 2);

    if (!s->temp || !s->src)
        return AVERROR(ENOMEM);
    return 0;
}