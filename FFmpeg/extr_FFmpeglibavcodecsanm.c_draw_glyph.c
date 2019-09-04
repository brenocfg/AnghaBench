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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int ptrdiff_t ;
typedef  int /*<<< orphan*/  int8_t ;
struct TYPE_3__ {int /*<<< orphan*/ ** p4x4glyphs; int /*<<< orphan*/ ** p8x8glyphs; int /*<<< orphan*/  avctx; } ;
typedef  TYPE_1__ SANMVideoContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int NGLYPHS ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int draw_glyph(SANMVideoContext *ctx, uint16_t *dst, int index,
                      uint16_t fg_color, uint16_t bg_color, int block_size,
                      ptrdiff_t pitch)
{
    int8_t *pglyph;
    uint16_t colors[2] = { fg_color, bg_color };
    int x, y;

    if (index >= NGLYPHS) {
        av_log(ctx->avctx, AV_LOG_ERROR, "Ignoring nonexistent glyph #%u.\n", index);
        return AVERROR_INVALIDDATA;
    }

    pglyph = block_size == 8 ? ctx->p8x8glyphs[index] : ctx->p4x4glyphs[index];
    pitch -= block_size;

    for (y = 0; y < block_size; y++, dst += pitch)
        for (x = 0; x < block_size; x++)
            *dst++ = colors[*pglyph++];
    return 0;
}