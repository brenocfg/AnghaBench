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
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_15__ {TYPE_4__ const* sps; TYPE_2__** vps_list; int /*<<< orphan*/ * vps; } ;
struct TYPE_17__ {TYPE_3__ ps; void** sao_pixel_buffer_v; void** sao_pixel_buffer_h; TYPE_1__* avctx; int /*<<< orphan*/  vdsp; int /*<<< orphan*/  hevcdsp; int /*<<< orphan*/  hpc; } ;
struct TYPE_16__ {scalar_t__ chroma_format_idc; int width; int* hshift; int height; int* vshift; int ctb_height; int pixel_shift; int ctb_width; size_t vps_id; scalar_t__ sao_enabled; int /*<<< orphan*/  bit_depth; } ;
struct TYPE_14__ {scalar_t__ data; } ;
struct TYPE_13__ {int pix_fmt; int /*<<< orphan*/  hwaccel; } ;
typedef  int /*<<< orphan*/  HEVCVPS ;
typedef  TYPE_4__ HEVCSPS ;
typedef  TYPE_5__ HEVCContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (void**) ; 
 void* av_malloc (int) ; 
 int /*<<< orphan*/  export_stream_params (TYPE_5__*,TYPE_4__ const*) ; 
 int /*<<< orphan*/  ff_hevc_dsp_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_hevc_pred_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_videodsp_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pic_arrays_free (TYPE_5__*) ; 
 int pic_arrays_init (TYPE_5__*,TYPE_4__ const*) ; 

__attribute__((used)) static int set_sps(HEVCContext *s, const HEVCSPS *sps,
                   enum AVPixelFormat pix_fmt)
{
    int ret, i;

    pic_arrays_free(s);
    s->ps.sps = NULL;
    s->ps.vps = NULL;

    if (!sps)
        return 0;

    ret = pic_arrays_init(s, sps);
    if (ret < 0)
        goto fail;

    export_stream_params(s, sps);

    s->avctx->pix_fmt = pix_fmt;

    ff_hevc_pred_init(&s->hpc,     sps->bit_depth);
    ff_hevc_dsp_init (&s->hevcdsp, sps->bit_depth);
    ff_videodsp_init (&s->vdsp,    sps->bit_depth);

    for (i = 0; i < 3; i++) {
        av_freep(&s->sao_pixel_buffer_h[i]);
        av_freep(&s->sao_pixel_buffer_v[i]);
    }

    if (sps->sao_enabled && !s->avctx->hwaccel) {
        int c_count = (sps->chroma_format_idc != 0) ? 3 : 1;
        int c_idx;

        for(c_idx = 0; c_idx < c_count; c_idx++) {
            int w = sps->width >> sps->hshift[c_idx];
            int h = sps->height >> sps->vshift[c_idx];
            s->sao_pixel_buffer_h[c_idx] =
                av_malloc((w * 2 * sps->ctb_height) <<
                          sps->pixel_shift);
            s->sao_pixel_buffer_v[c_idx] =
                av_malloc((h * 2 * sps->ctb_width) <<
                          sps->pixel_shift);
        }
    }

    s->ps.sps = sps;
    s->ps.vps = (HEVCVPS*) s->ps.vps_list[s->ps.sps->vps_id]->data;

    return 0;

fail:
    pic_arrays_free(s);
    s->ps.sps = NULL;
    return ret;
}