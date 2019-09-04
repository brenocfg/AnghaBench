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
typedef  unsigned short uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/  g; int /*<<< orphan*/  avctx; } ;
typedef  TYPE_1__ SgiState ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_WN16A (unsigned short*,unsigned short) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 unsigned short bytestream2_get_be16u (int /*<<< orphan*/ *) ; 
 int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 unsigned short bytestream2_get_ne16 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int expand_rle_row16(SgiState *s, uint16_t *out_buf,
                            int len, int pixelstride)
{
    unsigned short pixel;
    unsigned char count;
    unsigned short *orig = out_buf;
    uint16_t *out_end = out_buf + len;

    while (out_buf < out_end) {
        if (bytestream2_get_bytes_left(&s->g) < 2)
            return AVERROR_INVALIDDATA;
        pixel = bytestream2_get_be16u(&s->g);
        if (!(count = (pixel & 0x7f)))
            break;

        /* Check for buffer overflow. */
        if (out_end - out_buf <= pixelstride * (count - 1)) {
            av_log(s->avctx, AV_LOG_ERROR, "Invalid pixel count.\n");
            return AVERROR_INVALIDDATA;
        }

        if (pixel & 0x80) {
            while (count--) {
                pixel = bytestream2_get_ne16(&s->g);
                AV_WN16A(out_buf, pixel);
                out_buf += pixelstride;
            }
        } else {
            pixel = bytestream2_get_ne16(&s->g);

            while (count--) {
                AV_WN16A(out_buf, pixel);
                out_buf += pixelstride;
            }
        }
    }
    return (out_buf - orig) / pixelstride;
}