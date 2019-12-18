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
struct TYPE_3__ {int stride; int /*<<< orphan*/ * pixel_ptr; int /*<<< orphan*/  stream_ptr; } ;
typedef  TYPE_1__ IpvideoContext ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  bytestream2_get_byte (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipvideo_decode_block_opcode_0xC(IpvideoContext *s, AVFrame *frame)
{
    int x, y;

    /* 16-color block encoding: each 2x2 block is a different color */
    for (y = 0; y < 8; y += 2) {
        for (x = 0; x < 8; x += 2) {
            s->pixel_ptr[x                ] =
            s->pixel_ptr[x + 1            ] =
            s->pixel_ptr[x +     s->stride] =
            s->pixel_ptr[x + 1 + s->stride] = bytestream2_get_byte(&s->stream_ptr);
        }
        s->pixel_ptr += s->stride * 2;
    }

    /* report success */
    return 0;
}