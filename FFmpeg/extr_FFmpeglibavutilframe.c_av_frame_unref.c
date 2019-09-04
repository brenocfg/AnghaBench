#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nb_extended_buf; int /*<<< orphan*/  private_ref; int /*<<< orphan*/  opaque_ref; int /*<<< orphan*/  hw_frames_ctx; int /*<<< orphan*/  metadata; int /*<<< orphan*/ * extended_buf; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  get_frame_defaults (TYPE_1__*) ; 
 int /*<<< orphan*/  wipe_side_data (TYPE_1__*) ; 

void av_frame_unref(AVFrame *frame)
{
    int i;

    if (!frame)
        return;

    wipe_side_data(frame);

    for (i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        av_buffer_unref(&frame->buf[i]);
    for (i = 0; i < frame->nb_extended_buf; i++)
        av_buffer_unref(&frame->extended_buf[i]);
    av_freep(&frame->extended_buf);
    av_dict_free(&frame->metadata);
#if FF_API_FRAME_QP
FF_DISABLE_DEPRECATION_WARNINGS
    av_buffer_unref(&frame->qp_table_buf);
FF_ENABLE_DEPRECATION_WARNINGS
#endif

    av_buffer_unref(&frame->hw_frames_ctx);

    av_buffer_unref(&frame->opaque_ref);
    av_buffer_unref(&frame->private_ref);

    get_frame_defaults(frame);
}