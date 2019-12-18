#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  color_range; int /*<<< orphan*/  color_matrix; int /*<<< orphan*/  color_transfer; int /*<<< orphan*/  color_prim; int /*<<< orphan*/  pix_fmt; } ;
struct TYPE_16__ {int next_frame; int* prefilter; int* nframes; int /*<<< orphan*/ * diff_max; int /*<<< orphan*/ * weight_fact_table; int /*<<< orphan*/ * exptable; int /*<<< orphan*/ * range; int /*<<< orphan*/ * patch_size; int /*<<< orphan*/ * origin_tune; int /*<<< orphan*/ * strength; int /*<<< orphan*/  functions; TYPE_2__ output; TYPE_6__* frame; } ;
typedef  TYPE_4__ hb_filter_private_t ;
struct TYPE_13__ {int /*<<< orphan*/  color_range; int /*<<< orphan*/  color_matrix; int /*<<< orphan*/  color_transfer; int /*<<< orphan*/  color_prim; } ;
struct TYPE_17__ {int /*<<< orphan*/  s; TYPE_3__* plane; TYPE_1__ f; } ;
typedef  TYPE_5__ hb_buffer_t ;
typedef  int /*<<< orphan*/  hb_buffer_list_t ;
struct TYPE_18__ {int /*<<< orphan*/  s; int /*<<< orphan*/ * plane; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_15__ {int /*<<< orphan*/  height; int /*<<< orphan*/  stride; int /*<<< orphan*/  width; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  NLMeansFunctions ;
typedef  TYPE_6__ Frame ;

/* Variables and functions */
 int NLMEANS_PREFILTER_MODE_PASSTHRU ; 
 int /*<<< orphan*/  hb_buffer_list_append (int /*<<< orphan*/ *,TYPE_5__*) ; 
 TYPE_5__* hb_buffer_list_clear (int /*<<< orphan*/ *) ; 
 TYPE_5__* hb_frame_buffer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmeans_deborder (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmeans_plane (int /*<<< orphan*/ *,TYPE_6__*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmeans_prefilter (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static hb_buffer_t * nlmeans_filter_flush(hb_filter_private_t *pv)
{
    hb_buffer_list_t list;

    hb_buffer_list_clear(&list);
    for (int f = 0; f < pv->next_frame; f++)
    {
        Frame *frame = &pv->frame[f];
        hb_buffer_t *buf;
        buf = hb_frame_buffer_init(pv->output.pix_fmt,
                                   frame->width, frame->height);
        buf->f.color_prim     = pv->output.color_prim;
        buf->f.color_transfer = pv->output.color_transfer;
        buf->f.color_matrix   = pv->output.color_matrix;
        buf->f.color_range    = pv->output.color_range ;

        NLMeansFunctions *functions = &pv->functions;

        for (int c = 0; c < 3; c++)
        {
            if (pv->prefilter[c] & NLMEANS_PREFILTER_MODE_PASSTHRU)
            {
                nlmeans_prefilter(&frame->plane[c], pv->prefilter[c]);
                nlmeans_deborder(&frame->plane[c], buf->plane[c].data,
                                 buf->plane[c].width, buf->plane[c].stride,
                                 buf->plane[c].height);
                continue;
            }
            if (pv->strength[c] == 0)
            {
                nlmeans_deborder(&frame->plane[c], buf->plane[c].data,
                                 buf->plane[c].width, buf->plane[c].stride,
                                 buf->plane[c].height);
                continue;
            }

            int nframes = pv->next_frame - f;
            if (pv->nframes[c] < nframes)
            {
                nframes = pv->nframes[c];
            }
            // Process current plane
            nlmeans_plane(functions,
                          frame,
                          pv->prefilter[c],
                          c,
                          nframes,
                          buf->plane[c].data,
                          buf->plane[c].width,
                          buf->plane[c].stride,
                          buf->plane[c].height,
                          pv->strength[c],
                          pv->origin_tune[c],
                          pv->patch_size[c],
                          pv->range[c],
                          pv->exptable[c],
                          pv->weight_fact_table[c],
                          pv->diff_max[c]);
        }
        buf->s = frame->s;
        hb_buffer_list_append(&list, buf);
    }
    return hb_buffer_list_clear(&list);
}