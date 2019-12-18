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
struct TYPE_10__ {int /*<<< orphan*/  color_range; int /*<<< orphan*/  color_matrix; int /*<<< orphan*/  color_transfer; int /*<<< orphan*/  color_prim; int /*<<< orphan*/  fmt; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_9__ {int flags; int /*<<< orphan*/  combed; int /*<<< orphan*/  duration; int /*<<< orphan*/  start; } ;
struct TYPE_11__ {TYPE_3__ f; TYPE_2__ s; TYPE_1__* plane; } ;
typedef  TYPE_4__ hb_buffer_t ;
struct TYPE_12__ {int interlaced_frame; int top_field_first; int /*<<< orphan*/  color_range; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  color_trc; int /*<<< orphan*/  color_primaries; int /*<<< orphan*/  format; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  reordered_opaque; int /*<<< orphan*/  pts; int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;
struct TYPE_8__ {int /*<<< orphan*/  stride; int /*<<< orphan*/  data; } ;
typedef  TYPE_5__ AVFrame ;

/* Variables and functions */
 int PIC_FLAG_TOP_FIELD_FIRST ; 
 int /*<<< orphan*/  hb_colr_mat_hb_to_ff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_colr_pri_hb_to_ff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_colr_tra_hb_to_ff (int /*<<< orphan*/ ) ; 

void hb_video_buffer_to_avframe(AVFrame *frame, hb_buffer_t * buf)
{
    frame->data[0]     = buf->plane[0].data;
    frame->data[1]     = buf->plane[1].data;
    frame->data[2]     = buf->plane[2].data;
    frame->linesize[0] = buf->plane[0].stride;
    frame->linesize[1] = buf->plane[1].stride;
    frame->linesize[2] = buf->plane[2].stride;

    frame->pts              = buf->s.start;
    frame->reordered_opaque = buf->s.duration;
    frame->width            = buf->f.width;
    frame->height           = buf->f.height;
    frame->format           = buf->f.fmt;
    frame->interlaced_frame = !!buf->s.combed;
    frame->top_field_first  = !!(buf->s.flags & PIC_FLAG_TOP_FIELD_FIRST);

    frame->format          = buf->f.fmt;
    frame->color_primaries = hb_colr_pri_hb_to_ff(buf->f.color_prim);
    frame->color_trc       = hb_colr_tra_hb_to_ff(buf->f.color_transfer);
    frame->colorspace      = hb_colr_mat_hb_to_ff(buf->f.color_matrix);
    frame->color_range     = buf->f.color_range;
}