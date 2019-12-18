#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_3__* priv; } ;
struct TYPE_14__ {void* w; void* h; int /*<<< orphan*/  format; TYPE_6__* dst; } ;
struct TYPE_13__ {int /*<<< orphan*/  log2_chroma_w; int /*<<< orphan*/  log2_chroma_h; TYPE_1__* comp; } ;
struct TYPE_12__ {int nb_threads; int depth; int max; int group_size; int group_bits; int pgroup_size; int block_size; scalar_t__ mode; int bm_range; int bm_step; int /*<<< orphan*/  get_block_row; int /*<<< orphan*/  do_block_ssd; int /*<<< orphan*/  do_output; void** planeheight; void** planewidth; TYPE_2__* slices; int /*<<< orphan*/  nb_planes; } ;
struct TYPE_11__ {void* search_positions; void* rbufferz; void* rbuffer; void* rbufferv; void* rbufferh; void* bufferz; void* buffer; void* bufferv; void* bufferh; void* gdcti; void* gdctf; void* dcti; void* dctf; void* den; void* num; } ;
struct TYPE_10__ {int depth; } ;
typedef  TYPE_2__ SliceContext ;
typedef  int /*<<< orphan*/  FFTSample ;
typedef  TYPE_3__ BM3DContext ;
typedef  TYPE_4__ AVPixFmtDescriptor ;
typedef  TYPE_5__ AVFilterLink ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 void* AV_CEIL_RSHIFT (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DCT_II ; 
 int /*<<< orphan*/  DCT_III ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFALIGN (void*,int) ; 
 int FFMIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FINAL ; 
 int /*<<< orphan*/  MAX_NB_THREADS ; 
 int SQR (int) ; 
 void* av_calloc (int,int) ; 
 void* av_dct_init (int,int /*<<< orphan*/ ) ; 
 int av_log2 (int) ; 
 int /*<<< orphan*/  av_pix_fmt_count_planes (int /*<<< orphan*/ ) ; 
 TYPE_4__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_block_ssd ; 
 int /*<<< orphan*/  do_block_ssd16 ; 
 int /*<<< orphan*/  do_output ; 
 int /*<<< orphan*/  do_output16 ; 
 int /*<<< orphan*/  ff_filter_get_nb_threads (TYPE_6__*) ; 
 int /*<<< orphan*/  get_block_row ; 
 int /*<<< orphan*/  get_block_row16 ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);
    AVFilterContext *ctx = inlink->dst;
    BM3DContext *s = ctx->priv;
    int i, group_bits;

    s->nb_threads = FFMIN(ff_filter_get_nb_threads(ctx), MAX_NB_THREADS);
    s->nb_planes = av_pix_fmt_count_planes(inlink->format);
    s->depth = desc->comp[0].depth;
    s->max = (1 << s->depth) - 1;
    s->planeheight[1] = s->planeheight[2] = AV_CEIL_RSHIFT(inlink->h, desc->log2_chroma_h);
    s->planeheight[0] = s->planeheight[3] = inlink->h;
    s->planewidth[1]  = s->planewidth[2]  = AV_CEIL_RSHIFT(inlink->w, desc->log2_chroma_w);
    s->planewidth[0]  = s->planewidth[3]  = inlink->w;

    for (group_bits = 4; 1 << group_bits < s->group_size; group_bits++);
    s->group_bits = group_bits;
    s->pgroup_size = 1 << group_bits;

    for (i = 0; i < s->nb_threads; i++) {
        SliceContext *sc = &s->slices[i];

        sc->num = av_calloc(FFALIGN(s->planewidth[0], s->block_size) * FFALIGN(s->planeheight[0], s->block_size), sizeof(FFTSample));
        sc->den = av_calloc(FFALIGN(s->planewidth[0], s->block_size) * FFALIGN(s->planeheight[0], s->block_size), sizeof(FFTSample));
        if (!sc->num || !sc->den)
            return AVERROR(ENOMEM);

        sc->dctf = av_dct_init(av_log2(s->block_size), DCT_II);
        sc->dcti = av_dct_init(av_log2(s->block_size), DCT_III);
        if (!sc->dctf || !sc->dcti)
            return AVERROR(ENOMEM);

        if (s->group_bits > 1) {
            sc->gdctf = av_dct_init(s->group_bits, DCT_II);
            sc->gdcti = av_dct_init(s->group_bits, DCT_III);
            if (!sc->gdctf || !sc->gdcti)
                return AVERROR(ENOMEM);
        }

        sc->buffer = av_calloc(s->block_size * s->block_size * s->pgroup_size, sizeof(*sc->buffer));
        sc->bufferz = av_calloc(s->block_size * s->block_size * s->pgroup_size, sizeof(*sc->bufferz));
        sc->bufferh = av_calloc(s->block_size * s->block_size, sizeof(*sc->bufferh));
        sc->bufferv = av_calloc(s->block_size * s->block_size, sizeof(*sc->bufferv));
        if (!sc->bufferh || !sc->bufferv || !sc->buffer || !sc->bufferz)
            return AVERROR(ENOMEM);

        if (s->mode == FINAL) {
            sc->rbuffer = av_calloc(s->block_size * s->block_size * s->pgroup_size, sizeof(*sc->rbuffer));
            sc->rbufferz = av_calloc(s->block_size * s->block_size * s->pgroup_size, sizeof(*sc->rbufferz));
            sc->rbufferh = av_calloc(s->block_size * s->block_size, sizeof(*sc->rbufferh));
            sc->rbufferv = av_calloc(s->block_size * s->block_size, sizeof(*sc->rbufferv));
            if (!sc->rbufferh || !sc->rbufferv || !sc->rbuffer || !sc->rbufferz)
                return AVERROR(ENOMEM);
        }

        sc->search_positions = av_calloc(SQR(2 * s->bm_range / s->bm_step + 1), sizeof(*sc->search_positions));
        if (!sc->search_positions)
            return AVERROR(ENOMEM);
    }

    s->do_output = do_output;
    s->do_block_ssd = do_block_ssd;
    s->get_block_row = get_block_row;

    if (s->depth > 8) {
        s->do_output = do_output16;
        s->do_block_ssd = do_block_ssd16;
        s->get_block_row = get_block_row16;
    }

    return 0;
}