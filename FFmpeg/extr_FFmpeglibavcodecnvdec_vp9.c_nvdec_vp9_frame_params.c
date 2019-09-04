#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  AVCodecContext ;
typedef  int /*<<< orphan*/  AVBufferRef ;

/* Variables and functions */
 int ff_nvdec_frame_params (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nvdec_vp9_frame_params(AVCodecContext *avctx,
                                  AVBufferRef *hw_frames_ctx)
{
    // VP9 uses a fixed size pool of 8 possible reference frames
    return ff_nvdec_frame_params(avctx, hw_frames_ctx, 8, 0);
}