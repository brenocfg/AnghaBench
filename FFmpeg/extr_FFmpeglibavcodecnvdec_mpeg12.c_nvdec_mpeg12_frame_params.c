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

__attribute__((used)) static int nvdec_mpeg12_frame_params(AVCodecContext *avctx,
                                  AVBufferRef *hw_frames_ctx)
{
    // Each frame can at most have one P and one B reference
    return ff_nvdec_frame_params(avctx, hw_frames_ctx, 2, 0);
}