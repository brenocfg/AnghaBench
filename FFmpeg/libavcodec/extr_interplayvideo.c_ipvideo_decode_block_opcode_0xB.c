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
struct TYPE_3__ {scalar_t__ stride; int /*<<< orphan*/  pixel_ptr; int /*<<< orphan*/  stream_ptr; } ;
typedef  TYPE_1__ IpvideoContext ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  bytestream2_get_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ipvideo_decode_block_opcode_0xB(IpvideoContext *s, AVFrame *frame)
{
    int y;

    /* 64-color encoding (each pixel in block is a different color) */
    for (y = 0; y < 8; y++) {
        bytestream2_get_buffer(&s->stream_ptr, s->pixel_ptr, 8);
        s->pixel_ptr  += s->stride;
    }

    /* report success */
    return 0;
}