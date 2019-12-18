#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ old_width; scalar_t__ width; int old_height; int height; int framebuf_stride; int compression; int old_tile_w; int tile_width; int old_tile_h; int tile_height; int tile_stride; int epic_buf_stride; void* epic_buf_base; int /*<<< orphan*/ * epic_buf; void* kempf_flags; void* kempf_buf; void* jpeg_tile; void* synth_tile; int /*<<< orphan*/  framebuf; } ;
typedef  TYPE_1__ G2MContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFALIGN (int,int) ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_freep (void**) ; 
 void* av_mallocz (int) ; 
 int /*<<< orphan*/  av_mallocz_array (int,int) ; 

__attribute__((used)) static int g2m_init_buffers(G2MContext *c)
{
    int aligned_height;

    if (!c->framebuf || c->old_width < c->width || c->old_height < c->height) {
        c->framebuf_stride = FFALIGN(c->width + 15, 16) * 3;
        aligned_height     = c->height + 15;
        av_free(c->framebuf);
        c->framebuf = av_mallocz_array(c->framebuf_stride, aligned_height);
        if (!c->framebuf)
            return AVERROR(ENOMEM);
    }
    if (!c->synth_tile || !c->jpeg_tile ||
        (c->compression == 2 && !c->epic_buf_base) ||
        c->old_tile_w < c->tile_width ||
        c->old_tile_h < c->tile_height) {
        c->tile_stride     = FFALIGN(c->tile_width, 16) * 3;
        c->epic_buf_stride = FFALIGN(c->tile_width * 4, 16);
        aligned_height     = FFALIGN(c->tile_height,    16);
        av_freep(&c->synth_tile);
        av_freep(&c->jpeg_tile);
        av_freep(&c->kempf_buf);
        av_freep(&c->kempf_flags);
        av_freep(&c->epic_buf_base);
        c->epic_buf    = NULL;
        c->synth_tile  = av_mallocz(c->tile_stride      * aligned_height);
        c->jpeg_tile   = av_mallocz(c->tile_stride      * aligned_height);
        c->kempf_buf   = av_mallocz((c->tile_width + 1) * aligned_height +
                                    AV_INPUT_BUFFER_PADDING_SIZE);
        c->kempf_flags = av_mallocz(c->tile_width       * aligned_height);
        if (!c->synth_tile || !c->jpeg_tile ||
            !c->kempf_buf || !c->kempf_flags)
            return AVERROR(ENOMEM);
        if (c->compression == 2) {
            c->epic_buf_base = av_mallocz(c->epic_buf_stride * aligned_height + 4);
            if (!c->epic_buf_base)
                return AVERROR(ENOMEM);
            c->epic_buf = c->epic_buf_base + 4;
        }
    }

    return 0;
}