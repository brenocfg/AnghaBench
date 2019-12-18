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
struct TYPE_4__ {int /*<<< orphan*/  second_last_frame; int /*<<< orphan*/  avctx; int /*<<< orphan*/  mv_ptr; int /*<<< orphan*/  stream_ptr; int /*<<< orphan*/  is_16bpp; } ;
typedef  TYPE_1__ IpvideoContext ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 unsigned char bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 int copy_from (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ff_tlog (int /*<<< orphan*/ ,char*,unsigned char,int,int) ; 

__attribute__((used)) static int ipvideo_decode_block_opcode_0x2(IpvideoContext *s, AVFrame *frame)
{
    unsigned char B;
    int x, y;

    /* copy block from 2 frames ago using a motion vector; need 1 more byte */
    if (!s->is_16bpp) {
        B = bytestream2_get_byte(&s->stream_ptr);
    } else {
        B = bytestream2_get_byte(&s->mv_ptr);
    }

    if (B < 56) {
        x = 8 + (B % 7);
        y = B / 7;
    } else {
        x = -14 + ((B - 56) % 29);
        y =   8 + ((B - 56) / 29);
    }

    ff_tlog(s->avctx, "motion byte = %d, (x, y) = (%d, %d)\n", B, x, y);
    return copy_from(s, s->second_last_frame, frame, x, y);
}