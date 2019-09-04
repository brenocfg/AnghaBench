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
struct TYPE_3__ {int* pal; int /*<<< orphan*/  stream; int /*<<< orphan*/  avctx; } ;
typedef  TYPE_1__ VBDecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int bytestream2_get_be24 (int /*<<< orphan*/ *) ; 
 int bytestream2_get_byte (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vb_decode_palette(VBDecContext *c, int data_size)
{
    int start, size, i;

    start = bytestream2_get_byte(&c->stream);
    size  = (bytestream2_get_byte(&c->stream) - 1) & 0xFF;
    if (start + size > 255) {
        av_log(c->avctx, AV_LOG_ERROR, "Palette change runs beyond entry 256\n");
        return;
    }
    if (size*3+2 > data_size) {
        av_log(c->avctx, AV_LOG_ERROR, "Palette data runs beyond chunk size\n");
        return;
    }
    for (i = start; i <= start + size; i++)
        c->pal[i] = 0xFFU << 24 | bytestream2_get_be24(&c->stream);
}