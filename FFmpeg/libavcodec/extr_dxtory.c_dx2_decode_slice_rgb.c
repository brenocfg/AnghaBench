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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int width; int* linesize; int /*<<< orphan*/ ** data; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  decode_sym (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dx2_decode_slice_rgb(GetBitContext *gb, AVFrame *frame,
                                int line, int left, uint8_t lru[3][8])
{
    int x, y;
    int width    = frame->width;
    int stride   = frame->linesize[0];
    uint8_t *dst = frame->data[0] + stride * line;

    for (y = 0; y < left && get_bits_left(gb) > 6 * width; y++) {
        for (x = 0; x < width; x++) {
            dst[x * 3 + 0] = decode_sym(gb, lru[0]);
            dst[x * 3 + 1] = decode_sym(gb, lru[1]);
            dst[x * 3 + 2] = decode_sym(gb, lru[2]);
        }

        dst += stride;
    }

    return y;
}