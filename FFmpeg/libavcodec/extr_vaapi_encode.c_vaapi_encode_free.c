#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int nb_slices; scalar_t__ output_buffer; TYPE_4__* roi; TYPE_4__* codec_picture_params; TYPE_4__* priv_data; TYPE_4__* slices; TYPE_4__* param_buffers; int /*<<< orphan*/  recon_image; int /*<<< orphan*/  input_image; scalar_t__ encode_issued; } ;
typedef  TYPE_1__ VAAPIEncodePicture ;
struct TYPE_7__ {struct TYPE_7__* codec_slice_params; struct TYPE_7__* priv_data; } ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 scalar_t__ VA_INVALID_ID ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_free (TYPE_1__*) ; 
 int /*<<< orphan*/  av_freep (TYPE_4__**) ; 
 int /*<<< orphan*/  vaapi_encode_discard (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int vaapi_encode_free(AVCodecContext *avctx,
                             VAAPIEncodePicture *pic)
{
    int i;

    if (pic->encode_issued)
        vaapi_encode_discard(avctx, pic);

    for (i = 0; i < pic->nb_slices; i++) {
        if (pic->slices) {
            av_freep(&pic->slices[i].priv_data);
            av_freep(&pic->slices[i].codec_slice_params);
        }
    }
    av_freep(&pic->codec_picture_params);

    av_frame_free(&pic->input_image);
    av_frame_free(&pic->recon_image);

    av_freep(&pic->param_buffers);
    av_freep(&pic->slices);
    // Output buffer should already be destroyed.
    av_assert0(pic->output_buffer == VA_INVALID_ID);

    av_freep(&pic->priv_data);
    av_freep(&pic->codec_picture_params);
    av_freep(&pic->roi);

    av_free(pic);

    return 0;
}