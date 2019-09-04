#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_6__ {int /*<<< orphan*/  second_last_frame; TYPE_1__* avctx; scalar_t__ stride; int /*<<< orphan*/  pixel_ptr; int /*<<< orphan*/  stream_ptr; } ;
struct TYPE_5__ {int frame_number; } ;
typedef  TYPE_2__ IpvideoContext ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  bytestream2_get_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  copy_from (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipvideo_format_06_firstpass(IpvideoContext *s, AVFrame *frame, int16_t opcode)
{
    int line;

    if (!opcode) {
        for (line = 0; line < 8; ++line) {
            bytestream2_get_buffer(&s->stream_ptr, s->pixel_ptr, 8);
            s->pixel_ptr += s->stride;
        }
    } else {
        /* Don't try to copy second_last_frame data on the first frames */
        if (s->avctx->frame_number > 2)
            copy_from(s, s->second_last_frame, frame, 0, 0);
    }
}