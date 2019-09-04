#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * outputs; TYPE_1__* priv; int /*<<< orphan*/ ** inputs; } ;
struct TYPE_8__ {TYPE_3__* parent; } ;
struct TYPE_7__ {int /*<<< orphan*/  palette_loaded; } ;
typedef  TYPE_1__ PaletteUseContext ;
typedef  TYPE_2__ FFFrameSync ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  int /*<<< orphan*/  AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR_BUG ; 
 int apply_palette (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 int ff_filter_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ff_framesync_dualinput_get_writable (TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  load_palette (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int load_apply_palette(FFFrameSync *fs)
{
    AVFilterContext *ctx = fs->parent;
    AVFilterLink *inlink = ctx->inputs[0];
    PaletteUseContext *s = ctx->priv;
    AVFrame *master, *second, *out = NULL;
    int ret;

    // writable for error diffusal dithering
    ret = ff_framesync_dualinput_get_writable(fs, &master, &second);
    if (ret < 0)
        return ret;
    if (!master || !second) {
        ret = AVERROR_BUG;
        goto error;
    }
    if (!s->palette_loaded) {
        load_palette(s, second);
    }
    ret = apply_palette(inlink, master, &out);
    if (ret < 0)
        goto error;
    return ff_filter_frame(ctx->outputs[0], out);

error:
    av_frame_free(&master);
    return ret;
}