#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/ ** thread_ctx; int /*<<< orphan*/ * plane_ctx; } ;
typedef  TYPE_4__ hb_filter_private_t ;
struct TYPE_15__ {TYPE_4__* private_data; } ;
typedef  TYPE_5__ hb_filter_object_t ;
struct TYPE_13__ {int flags; } ;
struct TYPE_11__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  fmt; } ;
struct TYPE_16__ {TYPE_3__ s; TYPE_2__* plane; TYPE_1__ f; } ;
typedef  TYPE_6__ hb_buffer_t ;
typedef  int /*<<< orphan*/  chroma_smooth_thread_context_t ;
typedef  int /*<<< orphan*/  chroma_smooth_plane_context_t ;
struct TYPE_12__ {int /*<<< orphan*/  stride; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int HB_BUF_FLAG_EOF ; 
 int HB_FILTER_DONE ; 
 int HB_FILTER_OK ; 
 int /*<<< orphan*/  chroma_smooth (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_6__* hb_frame_buffer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int chroma_smooth_work_thread(hb_filter_object_t *filter,
                                     hb_buffer_t ** buf_in,
                                     hb_buffer_t ** buf_out, int thread)
{
    hb_filter_private_t *pv = filter->private_data;
    hb_buffer_t *in = *buf_in, *out;

    if (in->s.flags & HB_BUF_FLAG_EOF)
    {
        *buf_out = in;
        *buf_in = NULL;
        return HB_FILTER_DONE;
    }

    out = hb_frame_buffer_init(in->f.fmt, in->f.width, in->f.height);

    int c;
    for (c = 0; c < 3; c++)
    {
        chroma_smooth_plane_context_t  * ctx  = &pv->plane_ctx[c];
        chroma_smooth_thread_context_t * tctx = &pv->thread_ctx[thread][c];

        chroma_smooth(in->plane[c].data,
                      out->plane[c].data,
                      in->plane[c].width,
                      in->plane[c].height,
                      in->plane[c].stride,
                      ctx, tctx);
    }

    out->s = in->s;
    *buf_out = out;

    return HB_FILTER_OK;
}