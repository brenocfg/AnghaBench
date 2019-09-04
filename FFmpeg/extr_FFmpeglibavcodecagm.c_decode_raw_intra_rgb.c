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
typedef  scalar_t__ uint8_t ;
struct TYPE_6__ {int height; int width; } ;
struct TYPE_5__ {int* linesize; scalar_t__** data; } ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  TYPE_1__ AVFrame ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ bytestream2_get_byte (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_raw_intra_rgb(AVCodecContext *avctx, GetByteContext *gbyte, AVFrame *frame)
{
    uint8_t *dst = frame->data[0] + (avctx->height - 1) * frame->linesize[0];
    uint8_t r = 0, g = 0, b = 0;

    for (int y = 0; y < avctx->height; y++) {
        for (int x = 0; x < avctx->width; x++) {
            dst[x*3+0] = bytestream2_get_byte(gbyte) + r;
            r = dst[x*3+0];
            dst[x*3+1] = bytestream2_get_byte(gbyte) + g;
            g = dst[x*3+1];
            dst[x*3+2] = bytestream2_get_byte(gbyte) + b;
            b = dst[x*3+2];
        }
        dst -= frame->linesize[0];
    }

    return 0;
}