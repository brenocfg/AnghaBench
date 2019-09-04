#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct ColorSystem {int dummy; } ;
struct TYPE_10__ {int* linesize; scalar_t__* data; } ;
struct TYPE_9__ {TYPE_2__** outputs; TYPE_1__* priv; } ;
struct TYPE_8__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct TYPE_7__ {size_t color_system; int size; int /*<<< orphan*/  contrast; int /*<<< orphan*/  correct_gamma; int /*<<< orphan*/  cie; scalar_t__ i; TYPE_4__* f; } ;
typedef  TYPE_1__ CiescopeContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct ColorSystem* color_systems ; 
 TYPE_4__* ff_get_video_buffer (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_in_tongue (int /*<<< orphan*/ *,int,int,int,int,struct ColorSystem const*,double const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tongue_outline (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int draw_background(AVFilterContext *ctx)
{
    CiescopeContext *s = ctx->priv;
    const struct ColorSystem *cs = &color_systems[s->color_system];
    AVFilterLink *outlink = ctx->outputs[0];
    int w = s->size;
    int h = s->size;
    uint16_t *pixels;

    if ((s->f = ff_get_video_buffer(outlink, outlink->w, outlink->h)) == NULL)
        return AVERROR(ENOMEM);
    pixels = (uint16_t *)s->f->data[0];

    tongue_outline(pixels, s->f->linesize[0] / 2, w, h, 65535, s->cie);

    fill_in_tongue(pixels, s->f->linesize[0] / 2, w, h, 65535, cs, (const double (*)[3])s->i, s->cie,
                   s->correct_gamma, s->contrast);

    return 0;
}