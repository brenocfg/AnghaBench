#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  slice_buffers; scalar_t__ slices_allocated; scalar_t__ nb_slices; scalar_t__ nb_param_buffers; } ;
typedef  TYPE_1__ VAAPIDecodePicture ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_vaapi_decode_destroy_buffers (int /*<<< orphan*/ *,TYPE_1__*) ; 

int ff_vaapi_decode_cancel(AVCodecContext *avctx,
                           VAAPIDecodePicture *pic)
{
    ff_vaapi_decode_destroy_buffers(avctx, pic);

    pic->nb_param_buffers = 0;
    pic->nb_slices        = 0;
    pic->slices_allocated = 0;
    av_freep(&pic->slice_buffers);

    return 0;
}