#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int uint32_t ;
struct TYPE_17__ {int h; int w; TYPE_2__* dst; } ;
struct TYPE_16__ {size_t** data; int /*<<< orphan*/ * linesize; int /*<<< orphan*/  pts; } ;
struct TYPE_15__ {size_t* rgba_map; size_t* codeword; int* codebook; int codebook_length; size_t* codeword_closest_codebook_idxs; TYPE_1__* pix_desc; scalar_t__ pal8; int /*<<< orphan*/  lfg; int /*<<< orphan*/  max_steps_nb; int /*<<< orphan*/  codeword_length; } ;
struct TYPE_14__ {TYPE_5__** outputs; TYPE_3__* priv; } ;
struct TYPE_13__ {int /*<<< orphan*/  nb_components; } ;
typedef  TYPE_3__ ELBGContext ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVFilterLink ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 size_t B ; 
 int /*<<< orphan*/  ENOMEM ; 
 size_t G ; 
 int NB_COMPONENTS ; 
 size_t R ; 
 int /*<<< orphan*/  av_frame_free (TYPE_4__**) ; 
 int /*<<< orphan*/  avpriv_do_elbg (size_t*,int,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avpriv_init_elbg (size_t*,int,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ *) ; 
 int ff_filter_frame (TYPE_5__*,TYPE_4__*) ; 
 TYPE_4__* ff_get_video_buffer (TYPE_5__*,int,int) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *frame)
{
    ELBGContext *elbg = inlink->dst->priv;
    int i, j, k;
    uint8_t *p, *p0;

    const uint8_t r_idx  = elbg->rgba_map[R];
    const uint8_t g_idx  = elbg->rgba_map[G];
    const uint8_t b_idx  = elbg->rgba_map[B];

    /* build the codeword */
    p0 = frame->data[0];
    k = 0;
    for (i = 0; i < inlink->h; i++) {
        p = p0;
        for (j = 0; j < inlink->w; j++) {
            elbg->codeword[k++] = p[r_idx];
            elbg->codeword[k++] = p[g_idx];
            elbg->codeword[k++] = p[b_idx];
            p += elbg->pix_desc->nb_components;
        }
        p0 += frame->linesize[0];
    }

    /* compute the codebook */
    avpriv_init_elbg(elbg->codeword, NB_COMPONENTS, elbg->codeword_length,
                     elbg->codebook, elbg->codebook_length, elbg->max_steps_nb,
                     elbg->codeword_closest_codebook_idxs, &elbg->lfg);
    avpriv_do_elbg(elbg->codeword, NB_COMPONENTS, elbg->codeword_length,
                   elbg->codebook, elbg->codebook_length, elbg->max_steps_nb,
                   elbg->codeword_closest_codebook_idxs, &elbg->lfg);

    if (elbg->pal8) {
        AVFilterLink *outlink = inlink->dst->outputs[0];
        AVFrame *out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
        uint32_t *pal;

        if (!out) {
            av_frame_free(&frame);
            return AVERROR(ENOMEM);
        }
        out->pts = frame->pts;
        av_frame_free(&frame);
        pal = (uint32_t *)out->data[1];
        p0 = (uint8_t *)out->data[0];

        for (i = 0; i < elbg->codebook_length; i++) {
            pal[i] =  0xFFU                 << 24  |
                     (elbg->codebook[i*3  ] << 16) |
                     (elbg->codebook[i*3+1] <<  8) |
                      elbg->codebook[i*3+2];
        }

        k = 0;
        for (i = 0; i < inlink->h; i++) {
            p = p0;
            for (j = 0; j < inlink->w; j++, p++) {
                p[0] = elbg->codeword_closest_codebook_idxs[k++];
            }
            p0 += out->linesize[0];
        }

        return ff_filter_frame(outlink, out);
    }

    /* fill the output with the codebook values */
    p0 = frame->data[0];

    k = 0;
    for (i = 0; i < inlink->h; i++) {
        p = p0;
        for (j = 0; j < inlink->w; j++) {
            int cb_idx = NB_COMPONENTS * elbg->codeword_closest_codebook_idxs[k++];
            p[r_idx] = elbg->codebook[cb_idx];
            p[g_idx] = elbg->codebook[cb_idx+1];
            p[b_idx] = elbg->codebook[cb_idx+2];
            p += elbg->pix_desc->nb_components;
        }
        p0 += frame->linesize[0];
    }

    return ff_filter_frame(inlink->dst->outputs[0], frame);
}