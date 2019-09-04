#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* data; } ;
struct TYPE_5__ {int nb_coded_side_data; scalar_t__ extradata_size; scalar_t__ subtitle_header_size; TYPE_4__* coded_side_data; int /*<<< orphan*/  hw_device_ctx; int /*<<< orphan*/  hw_frames_ctx; TYPE_4__* subtitle_header; TYPE_4__* extradata; TYPE_4__* inter_matrix; TYPE_4__* intra_matrix; TYPE_4__* rc_override; } ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (TYPE_4__**) ; 
 int /*<<< orphan*/  av_opt_free (TYPE_1__*) ; 

__attribute__((used)) static void copy_context_reset(AVCodecContext *avctx)
{
    int i;

    av_opt_free(avctx);
#if FF_API_CODED_FRAME
FF_DISABLE_DEPRECATION_WARNINGS
    av_frame_free(&avctx->coded_frame);
FF_ENABLE_DEPRECATION_WARNINGS
#endif
    av_freep(&avctx->rc_override);
    av_freep(&avctx->intra_matrix);
    av_freep(&avctx->inter_matrix);
    av_freep(&avctx->extradata);
    av_freep(&avctx->subtitle_header);
    av_buffer_unref(&avctx->hw_frames_ctx);
    av_buffer_unref(&avctx->hw_device_ctx);
    for (i = 0; i < avctx->nb_coded_side_data; i++)
        av_freep(&avctx->coded_side_data[i].data);
    av_freep(&avctx->coded_side_data);
    avctx->subtitle_header_size = 0;
    avctx->nb_coded_side_data = 0;
    avctx->extradata_size = 0;
}