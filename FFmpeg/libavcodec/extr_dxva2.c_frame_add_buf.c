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
struct TYPE_3__ {scalar_t__* buf; } ;
typedef  TYPE_1__ AVFrame ;
typedef  int /*<<< orphan*/  AVBufferRef ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_NUM_DATA_POINTERS ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ av_buffer_ref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int frame_add_buf(AVFrame *frame, AVBufferRef *ref)
{
    int i;

    for (i = 0; i < AV_NUM_DATA_POINTERS; i++) {
        if (!frame->buf[i]) {
            frame->buf[i] = av_buffer_ref(ref);
            return frame->buf[i] ? 0 : AVERROR(ENOMEM);
        }
    }

    // For now we expect that the caller does not use more than
    // AV_NUM_DATA_POINTERS-1 buffers if the user uses a custom pool.
    return AVERROR(EINVAL);
}