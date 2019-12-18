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
typedef  int uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ Ir2Context ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int IR2_CODES ; 
 int av_clip_uint8 (int) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int ir2_get_code (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ir2_decode_plane(Ir2Context *ctx, int width, int height, uint8_t *dst,
                            int pitch, const uint8_t *table)
{
    int i;
    int j;
    int out = 0;

    if ((width & 1) || width * height / (2*(IR2_CODES - 0x7F)) > get_bits_left(&ctx->gb))
        return AVERROR_INVALIDDATA;

    /* first line contain absolute values, other lines contain deltas */
    while (out < width) {
        int c = ir2_get_code(&ctx->gb);
        if (c >= 0x80) { /* we have a run */
            c -= 0x7F;
            if (out + c*2 > width)
                return AVERROR_INVALIDDATA;
            for (i = 0; i < c * 2; i++)
                dst[out++] = 0x80;
        } else { /* copy two values from table */
            if (c <= 0)
                return AVERROR_INVALIDDATA;
            dst[out++] = table[c * 2];
            dst[out++] = table[(c * 2) + 1];
        }
    }
    dst += pitch;

    for (j = 1; j < height; j++) {
        out = 0;
        while (out < width) {
            int c;
            if (get_bits_left(&ctx->gb) <= 0)
                return AVERROR_INVALIDDATA;
            c = ir2_get_code(&ctx->gb);
            if (c >= 0x80) { /* we have a skip */
                c -= 0x7F;
                if (out + c*2 > width)
                    return AVERROR_INVALIDDATA;
                for (i = 0; i < c * 2; i++) {
                    dst[out] = dst[out - pitch];
                    out++;
                }
            } else { /* add two deltas from table */
                int t;
                if (c <= 0)
                    return AVERROR_INVALIDDATA;
                t        = dst[out - pitch] + (table[c * 2] - 128);
                t        = av_clip_uint8(t);
                dst[out] = t;
                out++;
                t        = dst[out - pitch] + (table[(c * 2) + 1] - 128);
                t        = av_clip_uint8(t);
                dst[out] = t;
                out++;
            }
        }
        dst += pitch;
    }
    return 0;
}