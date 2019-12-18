#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lapsharp_plane_context_t ;
struct TYPE_14__ {int /*<<< orphan*/  color_range; int /*<<< orphan*/  color_matrix; int /*<<< orphan*/  color_transfer; int /*<<< orphan*/  color_prim; int /*<<< orphan*/  pix_fmt; } ;
struct TYPE_17__ {int /*<<< orphan*/ * plane_ctx; TYPE_2__ output; } ;
typedef  TYPE_5__ hb_filter_private_t ;
struct TYPE_18__ {TYPE_5__* private_data; } ;
typedef  TYPE_6__ hb_filter_object_t ;
struct TYPE_16__ {int flags; } ;
struct TYPE_13__ {int /*<<< orphan*/  color_range; int /*<<< orphan*/  color_matrix; int /*<<< orphan*/  color_transfer; int /*<<< orphan*/  color_prim; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_19__ {TYPE_4__ s; TYPE_3__* plane; TYPE_1__ f; } ;
typedef  TYPE_7__ hb_buffer_t ;
struct TYPE_15__ {int /*<<< orphan*/  stride; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int HB_BUF_FLAG_EOF ; 
 int HB_FILTER_DONE ; 
 int HB_FILTER_OK ; 
 TYPE_7__* hb_frame_buffer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_frame_buffer_mirror_stride (TYPE_7__*) ; 
 int /*<<< orphan*/  hb_lapsharp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hb_lapsharp_work(hb_filter_object_t *filter,
                           hb_buffer_t ** buf_in,
                           hb_buffer_t ** buf_out)
{
    hb_filter_private_t *pv = filter->private_data;
    hb_buffer_t *in = *buf_in, *out;

    if (in->s.flags & HB_BUF_FLAG_EOF)
    {
        *buf_out = in;
        *buf_in = NULL;
        return HB_FILTER_DONE;
    }

    hb_frame_buffer_mirror_stride(in);
    out = hb_frame_buffer_init(pv->output.pix_fmt, in->f.width, in->f.height);
    out->f.color_prim     = pv->output.color_prim;
    out->f.color_transfer = pv->output.color_transfer;
    out->f.color_matrix   = pv->output.color_matrix;
    out->f.color_range    = pv->output.color_range ;

    int c;
    for (c = 0; c < 3; c++)
    {
        lapsharp_plane_context_t * ctx = &pv->plane_ctx[c];
        hb_lapsharp(in->plane[c].data,
                    out->plane[c].data,
                    in->plane[c].width,
                    in->plane[c].height,
                    in->plane[c].stride,
                    ctx);
    }

    out->s = in->s;
    *buf_out = out;

    return HB_FILTER_OK;
}