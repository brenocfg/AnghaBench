#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ nb_outputs; TYPE_2__** inputs; TYPE_1__** outputs; TYPE_3__* priv; } ;
struct TYPE_8__ {unsigned int* nb_streams; unsigned int nb_segments; } ;
struct TYPE_7__ {int /*<<< orphan*/  out_channel_layouts; int /*<<< orphan*/  out_samplerates; int /*<<< orphan*/  out_formats; } ;
struct TYPE_6__ {int /*<<< orphan*/  in_channel_layouts; int /*<<< orphan*/  in_samplerates; int /*<<< orphan*/  in_formats; } ;
typedef  TYPE_3__ ConcatContext ;
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  TYPE_4__ AVFilterContext ;
typedef  int /*<<< orphan*/  AVFilterChannelLayouts ;

/* Variables and functions */
 unsigned int AVMEDIA_TYPE_AUDIO ; 
 unsigned int TYPE_ALL ; 
 int /*<<< orphan*/ * ff_all_channel_layouts () ; 
 int /*<<< orphan*/ * ff_all_formats (unsigned int) ; 
 int /*<<< orphan*/ * ff_all_samplerates () ; 
 int ff_channel_layouts_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ff_formats_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    ConcatContext *cat = ctx->priv;
    unsigned type, nb_str, idx0 = 0, idx, str, seg;
    AVFilterFormats *formats, *rates = NULL;
    AVFilterChannelLayouts *layouts = NULL;
    int ret;

    for (type = 0; type < TYPE_ALL; type++) {
        nb_str = cat->nb_streams[type];
        for (str = 0; str < nb_str; str++) {
            idx = idx0;

            /* Set the output formats */
            formats = ff_all_formats(type);
            if ((ret = ff_formats_ref(formats, &ctx->outputs[idx]->in_formats)) < 0)
                return ret;

            if (type == AVMEDIA_TYPE_AUDIO) {
                rates = ff_all_samplerates();
                if ((ret = ff_formats_ref(rates, &ctx->outputs[idx]->in_samplerates)) < 0)
                    return ret;
                layouts = ff_all_channel_layouts();
                if ((ret = ff_channel_layouts_ref(layouts, &ctx->outputs[idx]->in_channel_layouts)) < 0)
                    return ret;
            }

            /* Set the same formats for each corresponding input */
            for (seg = 0; seg < cat->nb_segments; seg++) {
                if ((ret = ff_formats_ref(formats, &ctx->inputs[idx]->out_formats)) < 0)
                    return ret;
                if (type == AVMEDIA_TYPE_AUDIO) {
                    if ((ret = ff_formats_ref(rates, &ctx->inputs[idx]->out_samplerates)) < 0 ||
                        (ret = ff_channel_layouts_ref(layouts, &ctx->inputs[idx]->out_channel_layouts)) < 0)
                        return ret;
                }
                idx += ctx->nb_outputs;
            }

            idx0++;
        }
    }
    return 0;
}