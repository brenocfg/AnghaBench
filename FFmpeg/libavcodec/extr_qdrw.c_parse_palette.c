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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_4__ {scalar_t__ pix_fmt; } ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ AV_PIX_FMT_PAL8 ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,unsigned int) ; 
 unsigned int bytestream2_get_be16 (int /*<<< orphan*/ *) ; 
 int bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int parse_palette(AVCodecContext *avctx, GetByteContext *gbc,
                         uint32_t *pal, int colors, int pixmap)
{
    int i;

    for (i = 0; i <= colors; i++) {
        uint8_t r, g, b;
        unsigned int idx = bytestream2_get_be16(gbc); /* color index */
        if (idx > 255 && !pixmap) {
            av_log(avctx, AV_LOG_WARNING,
                   "Palette index out of range: %u\n", idx);
            bytestream2_skip(gbc, 6);
            continue;
        }
        if (avctx->pix_fmt != AV_PIX_FMT_PAL8)
            return AVERROR_INVALIDDATA;
        r = bytestream2_get_byte(gbc);
        bytestream2_skip(gbc, 1);
        g = bytestream2_get_byte(gbc);
        bytestream2_skip(gbc, 1);
        b = bytestream2_get_byte(gbc);
        bytestream2_skip(gbc, 1);
        pal[pixmap ? i : idx] = (0xFFU << 24) | (r << 16) | (g << 8) | b;
    }
    return 0;
}